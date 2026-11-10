#!/usr/bin/env python3
"""Build a replayable corpus of real source variants with simulated labels.

Each candidate changes the actual PolicyConfig.h schema consumed by the CTS
and Resizer kernels. Candidate acceptance is a simulated study label, never a
record of physical verification or a claim that 3,500 edits were installed.
"""
import argparse
import csv
import difflib
import hashlib
import json
from pathlib import Path
import random
import re
import subprocess

ROOT = Path(__file__).resolve().parents[2]
HOME = ROOT / 'learning_evolution'
DATA = HOME / 'dataset'
TARGET = 'src/cts/src/LearningPolicyConfig.h'
COUNT = 3500


def digest(value):
    return hashlib.sha256(value.encode()).hexdigest()


def patch_for(before, after, target):
    return ''.join(difflib.unified_diff(
        before.splitlines(keepends=True), after.splitlines(keepends=True),
        fromfile='a/' + target, tofile='b/' + target))


def replay(before, patch):
    """Strict unified-diff replay used to validate every stored candidate."""
    original = before.splitlines(keepends=True)
    output = []
    position = 0
    body = patch.splitlines(keepends=True)
    index = 2
    while index < len(body):
        match = re.match(r'@@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@', body[index])
        if not match:
            raise ValueError('Invalid patch hunk header')
        start = max(0, int(match[1]) - 1)
        if start < position:
            raise ValueError('Overlapping patch hunks')
        output.extend(original[position:start])
        position = start
        index += 1
        while index < len(body) and not body[index].startswith('@@'):
            line = body[index]
            if line[0] in ' -':
                if position >= len(original) or original[position] != line[1:]:
                    raise ValueError('Patch context mismatch')
                position += 1
            if line[0] in ' +':
                output.append(line[1:])
            if line[0] not in ' +-':
                raise ValueError('Unexpected patch line')
            index += 1
    output.extend(original[position:])
    return ''.join(output)


def config_variant(base, iteration, rng):
    """Mix small edits with larger parameter-and-control-choice edits."""
    fields = {
        'load_weight': f'{rng.uniform(.6, 1.6):.8f}',
        'density_weight': f'{rng.uniform(0, .6):.8f}',
        'prefix_weight': f'{rng.uniform(0, .5):.8f}',
        'neighborhood_weight': f'{rng.uniform(0, .4):.8f}',
        'late_weight': f'{rng.uniform(0, .3):.8f}',
        'critical_weight': f'{rng.uniform(0, .5):.8f}',
        'budget': str(rng.randint(4, 40)),
        'neighborhood': str(rng.randint(1, 16)),
        'spatial_mode': str(rng.randrange(3)),
        'use_dp': 'true' if rng.randrange(2) else 'false',
    }
    # Every seventh example is a small one-coefficient change.
    chosen = ['load_weight'] if iteration % 7 == 0 else list(fields)
    output = base
    for field in chosen:
        output, replacements = re.subn(
            rf'(\b{field}\s*=\s*)[^;]+;', rf'\g<1>{fields[field]};', output)
        if replacements != 1:
            raise ValueError('Missing or ambiguous policy field: ' + field)
    return output, chosen


def simulated_labels(rng, iteration):
    # No source-code effectiveness can be inferred from these invented labels.
    # Exactly 70% near-zero, 22% moderate and 8% rare higher-impact labels.
    bucket = (iteration - 1) % 100
    low, high = (0., 1.) if bucket < 70 else ((1.5, 2.5) if bucket < 92 else (4., 5.))
    wns = round(rng.uniform(low, high), 4)
    tns = round(rng.uniform(low, high), 4)
    runtime = round(rng.uniform(-.8, .3), 4)
    short = round(.5 * wns + .5 * tns, 4)
    long = round(short * rng.uniform(.5, 1.), 4)
    score = round(.45 * wns + .45 * tns - .1 * runtime, 4)
    return dict(simulated_wns_impact_pct=wns, simulated_tns_impact_pct=tns,
                simulated_runtime_delta_s=runtime,
                simulated_effectiveness=short,
                simulated_short_term_impact=short,
                simulated_long_term_impact=long,
                simulated_overall_score=score,
                simulated_accepted=wns > .2 and tns > .2 and score > .5,
                agent_iteration=iteration, generation=(iteration - 1) // 50,
                measured_openroad=False, applied_to_worktree=False,
                label_provenance='fictional study labels; no OpenROAD evaluation')


def generate_candidates():
    DATA.mkdir(exist_ok=True)
    variants = DATA / 'variants'
    patches = DATA / 'patches'
    variants.mkdir(exist_ok=True)
    patches.mkdir(exist_ok=True)
    # Only previously generated hash-named outputs are retired.
    for directory, pattern in [(variants, '*_new.h'), (patches, '*.patch')]:
        for path in directory.glob(pattern):
            if re.fullmatch(r'[0-9a-f]{64}(?:_new\.h|\.patch)', path.name):
                path.unlink()
    base = (ROOT / TARGET).read_text()
    (DATA / 'PolicyConfig_old.h').write_text(base)
    rng = random.Random(4173)
    labels_rng = random.Random(8192)
    rows = []
    for iteration in range(1, COUNT + 1):
        after, fields = config_variant(base, iteration, rng)
        patch = patch_for(base, after, TARGET)
        change_hash = digest(patch)
        relative_variant = f'learning_evolution/dataset/variants/{change_hash}_new.h'
        relative_patch = f'learning_evolution/dataset/patches/{change_hash}.patch'
        (ROOT / relative_variant).write_text(after)
        (ROOT / relative_patch).write_text(patch)
        if replay(base, patch) != after:
            raise AssertionError('Generated patch cannot be replayed')
        added = sum(line.startswith('+') and not line.startswith('+++') for line in patch.splitlines())
        removed = sum(line.startswith('-') and not line.startswith('---') for line in patch.splitlines())
        rows.append(dict(change_hash=change_hash, target_path=TARGET,
                         old_path='learning_evolution/dataset/PolicyConfig_old.h',
                         new_path=relative_variant, patch_path=relative_patch,
                         before_sha256=digest(base), after_sha256=digest(after),
                         candidate_kind='parameter and algorithm-choice variant',
                         changed_fields=';'.join(fields), lines_added=added,
                         lines_removed=removed, **simulated_labels(labels_rng, iteration)))
    if len({row['change_hash'] for row in rows}) != COUNT:
        raise AssertionError('Duplicate candidate changes')
    with (DATA / 'changes.csv').open('w', newline='') as handle:
        writer = csv.DictWriter(handle, fieldnames=list(rows[0]))
        writer.writeheader()
        writer.writerows(rows)
    (DATA / 'changes.jsonl').write_text(''.join(json.dumps(row) + '\n' for row in rows))
    (DATA / 'provenance.json').write_text(json.dumps(dict(
        candidate_count=COUNT, source_variant_seed=4173, label_seed=8192,
        source_target=TARGET, study_only=True, measured_openroad=False,
        description='Replayable source candidates with explicitly fictional impact labels.'), indent=2) + '\n')
    return rows


def applied_catalogue():
    """Hash actual applied source hunks; copied snapshots are excluded."""
    pairs = json.loads((HOME / 'source_pairs.json').read_text())
    sources = [(pair['new'], (ROOT / pair['old']).read_text(),
                (ROOT / pair['new']).read_text(), pair['old']) for pair in pairs]
    build_files = ['src/cts/src/CMakeLists.txt', 'src/cts/BUILD',
                   'src/rsz/src/CMakeLists.txt', 'src/rsz/BUILD']
    for path in build_files:
        old = 'learning_evolution/snapshots/' + path + '_old'
        sources.append((path, (ROOT / old).read_text(), (ROOT / path).read_text(), old))
    for path in [ROOT / 'src/cts/src/LearningMode.h', ROOT / 'src/cts/src/LearningPolicyConfig.h']:
        sources.append((str(path.relative_to(ROOT)), '', path.read_text(), ''))
    for directory in ['tests', 'tools']:
        for path in sorted((HOME / directory).glob('*')):
            if path.is_file() and path.suffix in {'.cpp', '.h', '.py', '.cjs'}:
                sources.append((str(path.relative_to(ROOT)), '', path.read_text(), ''))
    output = DATA / 'applied_hunks'
    output.mkdir(exist_ok=True)
    for obsolete in output.glob('*.patch'):
        if re.fullmatch(r'[0-9a-f]{64}\.patch', obsolete.name):
            obsolete.unlink()
    rows = []
    for target, before, after, old_path in sources:
        patch = patch_for(before, after, target)
        chunks = re.split(r'(?=^@@ )', patch, flags=re.MULTILINE)
        for chunk in chunks[1:]:
            header = re.match(r'@@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@', chunk)
            change_hash = digest(target + '\n' + chunk)
            stored_patch = '--- a/' + target + '\n+++ b/' + target + '\n' + chunk
            patch_path = f'learning_evolution/dataset/applied_hunks/{change_hash}.patch'
            (ROOT / patch_path).write_text(stored_patch)
            rows.append(dict(change_hash=change_hash, target_path=target,
                             old_path=old_path, new_path=target,
                             old_line=int(header[1]), new_line=int(header[3]),
                             lines_added=sum(line.startswith('+') for line in chunk.splitlines()),
                             lines_removed=sum(line.startswith('-') for line in chunk.splitlines()),
                             patch_path=patch_path, applied_to_worktree=True,
                             measured_openroad=False, validation='kernel checks only; full OpenROAD build not run'))
    with (DATA / 'applied_changes.csv').open('w', newline='') as handle:
        writer = csv.DictWriter(handle, fieldnames=list(rows[0]))
        writer.writeheader()
        writer.writerows(rows)
    return rows


def verify():
    with (DATA / 'changes.csv').open() as handle:
        rows = list(csv.DictReader(handle))
    if len(rows) != COUNT or len({r['change_hash'] for r in rows}) != COUNT:
        raise AssertionError('Candidate count/hash uniqueness mismatch')
    for row in rows:
        old = (ROOT / row['old_path']).read_text()
        new = (ROOT / row['new_path']).read_text()
        patch = (ROOT / row['patch_path']).read_text()
        if digest(patch) != row['change_hash'] or digest(old) != row['before_sha256']:
            raise AssertionError('Hash mismatch')
        if digest(new) != row['after_sha256'] or replay(old, patch) != new:
            raise AssertionError('Candidate replay mismatch')
    with (DATA / 'applied_changes.csv').open() as handle:
        applied = list(csv.DictReader(handle))
    for target in sorted({row['target_path'] for row in applied}):
        blocks = [row for row in applied if row['target_path'] == target]
        before = (ROOT / blocks[0]['old_path']).read_text() if blocks[0]['old_path'] else ''
        combined = '--- a/' + target + '\n+++ b/' + target + '\n'
        for block in blocks:
            stored = (ROOT / block['patch_path']).read_text()
            chunk = ''.join(stored.splitlines(keepends=True)[2:])
            if digest(target + '\n' + chunk) != block['change_hash']:
                raise AssertionError('Applied block hash mismatch')
            combined += chunk
        if replay(before, combined) != (ROOT / target).read_text():
            raise AssertionError('Applied source does not match catalogue: ' + target)
    for field in ['simulated_wns_impact_pct', 'simulated_tns_impact_pct']:
        values = [float(row[field]) for row in rows]
        if not all(0 <= value <= 5 for value in values):
            raise AssertionError('Impact outside [0, 5] percent')
        if sum(value <= 1 for value in values) != 2450:
            raise AssertionError('Expected 70 percent near-zero impacts')
        if sum(1.5 <= value <= 2.5 for value in values) != 770:
            raise AssertionError('Expected 22 percent moderate impacts')
        if sum(4 <= value <= 5 for value in values) != 280:
            raise AssertionError('Expected 8 percent higher impacts')
    # Sample the actual compiler against both small and larger candidates.
    for row in rows[:8]:
        subprocess.run(['g++', '-std=c++20', '-x', 'c++', '-fsyntax-only',
                        str(ROOT / row['new_path'])], check=True, capture_output=True)
    for pair in json.loads((HOME / 'source_pairs.json').read_text()):
        original = subprocess.check_output(['git', 'show', (HOME / 'BASE_REVISION.txt').read_text().strip() + ':' + pair['original']], cwd=ROOT)
        if original != (ROOT / pair['old']).read_bytes():
            raise AssertionError('Old source is not byte-identical to branch base')
    print(f'PASS: {len(rows)} unique source patches replayed and hashed; 8 variants syntax-checked; old sources verified')


def export_candidate(change_hash, destination):
    with (DATA / 'changes.csv').open() as handle:
        matches = [row for row in csv.DictReader(handle) if row['change_hash'] == change_hash]
    if len(matches) != 1:
        raise ValueError('Specify one complete change_hash from changes.csv')
    destination = Path(destination)
    destination.mkdir(parents=True, exist_ok=True)
    row = matches[0]
    (destination / 'PolicyConfig_new.h').write_bytes((ROOT / row['new_path']).read_bytes())
    (destination / 'change.patch').write_bytes((ROOT / row['patch_path']).read_bytes())
    print('Exported replayable study candidate to', destination)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('action', choices=['generate', 'verify', 'export'])
    parser.add_argument('--hash')
    parser.add_argument('--destination', default='/tmp/openroad-learning-candidate')
    args = parser.parse_args()
    if args.action == 'generate':
        rows = generate_candidates()
        applied = applied_catalogue()
        print(f'Created {len(rows)} proposed source variants and {len(applied)} applied hunk references')
    elif args.action == 'verify':
        verify()
    else:
        export_candidate(args.hash, args.destination)


if __name__ == '__main__':
    main()
