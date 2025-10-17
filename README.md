# ROOT Schema Evolution for ldmx-sw

This is a side-loading project in association with the `1815-schema-evolution` branch of ldmx-sw.

I am running things in v4.4.0 of ldmx-sw here (before the clang-tidy renaming) to produce
output files that have the old member variable names.

[`denv`](https://tomeichlersmith.github.io/denv) is used for interacting with ldmx-sw and ROOT
and the denv config is committed to this repo for reproducibility.

Additionally, some non-ldmx-sw test code is kept here in subdirectories in order to test run schema evolution
without the bulk of all of ldmx-sw. That test code is still run within this denv so that it uses
the same ROOT version that ldmx-sw would use.
