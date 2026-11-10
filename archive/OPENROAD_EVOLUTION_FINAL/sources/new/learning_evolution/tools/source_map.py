#!/usr/bin/env python3
"""Current source pointers; the self-contained final folder is the main index."""
import json
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
HOME=ROOT/'learning_evolution'


def main():
    pairs=json.loads((HOME/'source_pairs.json').read_text())
    embedded=json.loads((HOME/'embedded_kernels.json').read_text())
    lines=['# Start here', '', 'The complete review package is `suite/OPENROAD_EVOLUTION_FINAL/`.',
           'Open its `index.html` for graphs and clickable old/new comparisons, or `SOURCE_INDEX.md` in an editor.', '',
           'The former separate algorithm implementation directory has been removed. Definitions are inside the production files below.', '']
    for name,info in embedded.items():
        if not info.get('whole_file'):
            lines.append(f'- {name}: [{info["source"]}](../{info["source"]}) — search for `BEGIN INTEGRATED KERNEL {name}`.')
    lines+=['', '## Complete old/new source pairs', '']
    for pair in pairs:
        lines.append(f'- [{pair["old"]}](../{pair["old"]}) → [{pair["new"]}](../{pair["new"]})')
    (HOME/'START_HERE.md').write_text('\n'.join(lines)+'\n')


if __name__=='__main__':
    main()
