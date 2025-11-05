This is test code for a ROOT Forum post.

# Schema Evolution of a `std::map` Value Type

<hr>

_ROOT Version_: 6.34.04
_Platform_: linuxx8664gcc
_Compiler_: GCC 13.3.0

<hr>

Specifically, I am using the container image [ldmx/pro:v4.4.0 on DockerHub](https://hub.docker.com/layers/ldmx/pro/v4.4.0/images/sha256-3e2c25c7430441b5871d334b13a0ed93bcfa58cfe2fd6d88503040df7a1ae01f).

The source code for this example is available on GitHub: [tomeichlersmith/ldmx-root-schema-evolution-testbench](https://github.com/tomeichlersmith/ldmx-root-schema-evolution-testbench/tree/main) in the `forum/schema-evolve-std-map-value` subdirectory.

I have a simple class `Header` with two `int` members that have changed names.
The `v1` `Header` uses camel case names while the `v2` `Header` uses snake case names
and includes an updated `#pragma read` statement in its `LinkDef.h` file to be
able to evolve the `v1` schema into `v2`.

I can see that the schema evolution is being applied by injecting a printout
in the `#pragma read` statement, but the resulting values are all zero.

### Potentially related

There is a ROOT Forum post about renaming the contained type which has been
patched a few weeks ago, probably included in the next release.
I'm compiling the `master` branch of ROOT to see if this resolves my issue
before making my own forum post.
- https://root-forum.cern.ch/t/manual-schema-evolution-with-i-o-rules-and-branches-containing-vector-t/64026
- https://github.com/root-project/root/issues/19650
- https://github.com/root-project/root/pull/19688
- https://github.com/root-project/root/issues/19773
