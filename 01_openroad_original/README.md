# 01_openroad_original — READ-ONLY reference copy of the stock Resizer

- `rsz_snapshot/`: byte-exact copy of `external/OpenROAD/src/rsz` at the commit in `UPSTREAM_COMMIT.txt`.
- `sta_interface_snapshot/`: the dbSta / OpenSTA headers rsz calls into (context only, never built from here).

Nothing in this folder is ever edited. The framework restores the build slot from `rsz_snapshot/` after every candidate.
