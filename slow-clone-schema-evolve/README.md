This is test code for a ROOT Forum post.
https://root-forum.cern.ch/t/quiet-writing-failure-when-applying-schema-evolution-while-slow-cloning/64350

# Schema Evolution while Slow Cloning

<hr>

_ROOT Version_: 6.34.04
_Platform_: linuxx8664gcc
_Compiler_: GCC 13.3.0

<hr>

Specifically, I am using the container image [ldmx/pro:v4.4.0 on DockerHub](https://hub.docker.com/layers/ldmx/pro/v4.4.0/images/sha256-3e2c25c7430441b5871d334b13a0ed93bcfa58cfe2fd6d88503040df7a1ae01f).

I am working in a project where we recently adopted some naming guidelines for our member variables and have now applied them to classes that are serialized by ROOT into output TTrees. However, unsurprisingly, we still have data files with the old schema (old names for member variables) floating around and so I am interested in having some schema rules that rename the member variables when reading the old format.

The full project ldmx-sw is large and takes quite some time to compile, but I’ve been able to partially replicate the issue with a smaller example.

The source code for this example is available on GitHub: [tomeichlersmith/ldmx-root-schema-evolution-testbench](https://github.com/tomeichlersmith/ldmx-root-schema-evolution-testbench/tree/main) in the `slow-clone-schema-evolve` subdirectory.

I have a simple class `Header` with two `int` members that have changed names.
The `v1` `Header` uses camel case names while the `v2` `Header` uses snake case names
and includes an updated `#pragma read` statement in its `LinkDef.h` file to be
able to evolve the `v1` schema into `v2`.

Running the programs here shows all of the grizzly details, but the the summary is
- I can write, read, and copy[^0] a TTree of v1 while only using v1
- I can write, read, and copy a TTree of v2 while only using v2
- I can write v1 and read it with v2, but if I attempt to copy v1 with v2, the output file does not read correctly (even though the printouts while doing the copy are correct)
- I can avoid this write-out error by manually syncing the addresses between the input and output TTree (instead of using `CloneTree`), but then I cannot expect branches that are not "observed" while copying to be copied at all.

[^0]: When I say "copy" here, I mean "slow clone". I am focusing on slow cloning because our data processing framework slow clones while allowing the user to read some of the branches and potentially write new ones.

## Compile
Normal config and build cycle using CMake to find and configure the ROOT installation.
```
cmake -B build -S .
cmake --build build
```

## Run
Write a file using the old version of the Header object and attempt to read that
file with both the old and new versions.
Reading goes okay, but copying with the new schema and then reading does not go okay.

```
$./build/write-v1 v1-output.root
$ ./build/read-v1 v1-output.root
{ run: 42, event: 0 }
{ run: 42, event: 1 }
{ run: 42, event: 2 }
{ run: 42, event: 3 }
{ run: 42, event: 4 }
{ run: 42, event: 5 }
{ run: 42, event: 6 }
{ run: 42, event: 7 }
{ run: 42, event: 8 }
{ run: 42, event: 9 }
$ ./build/read-v2 v1-output.root
manual schema evolution rule being applied
{ run: 42, event: 0 }
manual schema evolution rule being applied
{ run: 42, event: 1 }
manual schema evolution rule being applied
{ run: 42, event: 2 }
manual schema evolution rule being applied
{ run: 42, event: 3 }
manual schema evolution rule being applied
{ run: 42, event: 4 }
manual schema evolution rule being applied
{ run: 42, event: 5 }
manual schema evolution rule being applied
{ run: 42, event: 6 }
manual schema evolution rule being applied
{ run: 42, event: 7 }
manual schema evolution rule being applied
{ run: 42, event: 8 }
manual schema evolution rule being applied
{ run: 42, event: 9 }
$ ./build/copy-v2-clone-tree v1-output.root v2-clone-tree-copy-v1-output.root
manual schema evolution rule being applied                                                                            
{ run: 42, event: 0 }                                                                                                 
manual schema evolution rule being applied                                                                            
{ run: 42, event: 1 }                                                                                                 
manual schema evolution rule being applied                                                                            
{ run: 42, event: 2 }                                                                                                 
manual schema evolution rule being applied
{ run: 42, event: 3 }
manual schema evolution rule being applied
{ run: 42, event: 4 }
manual schema evolution rule being applied
{ run: 42, event: 5 }
manual schema evolution rule being applied
{ run: 42, event: 6 }
manual schema evolution rule being applied
{ run: 42, event: 7 }
manual schema evolution rule being applied
{ run: 42, event: 8 }
manual schema evolution rule being applied
{ run: 42, event: 9 }
$ ./build/read-v2 v2-clone-tree-copy-v1-output.root
manual schema evolution rule being applied
{ run: -1904246784, event: -1904246784 }
manual schema evolution rule being applied
{ run: -1904246784, event: -1904246784 }
manual schema evolution rule being applied
{ run: -1904246784, event: -1904246784 }
manual schema evolution rule being applied
{ run: -1904246784, event: -1904246784 }
manual schema evolution rule being applied
{ run: -1904246784, event: -1904246784 }
manual schema evolution rule being applied
{ run: -1904246784, event: -1904246784 }
manual schema evolution rule being applied
{ run: -1904246784, event: -1904246784 }
manual schema evolution rule being applied
{ run: -1904246784, event: -1904246784 }
manual schema evolution rule being applied
{ run: -1904246784, event: -1904246784 }
manual schema evolution rule being applied
{ run: -1904246784, event: -1904246784 }
$ denv ./build/copy-v2-manual data/v1-out
put.root data/v2-copy-manual-v1-output.root                                                                           
manual schema evolution rule being applied                                                                            
{ run: 42, event: 0 }                                                                                                 
manual schema evolution rule being applied
{ run: 42, event: 1 }
manual schema evolution rule being applied
{ run: 42, event: 2 }
manual schema evolution rule being applied
{ run: 42, event: 3 }
manual schema evolution rule being applied
{ run: 42, event: 4 }
manual schema evolution rule being applied
{ run: 42, event: 5 }
manual schema evolution rule being applied
{ run: 42, event: 6 }
manual schema evolution rule being applied
{ run: 42, event: 7 }
manual schema evolution rule being applied
{ run: 42, event: 8 }
manual schema evolution rule being applied
{ run: 42, event: 9 }
$ denv ./build/read-v2 data/v2-copy-manual-v1-output.root 
{ run: 42, event: 0 }
{ run: 42, event: 1 }
{ run: 42, event: 2 }
{ run: 42, event: 3 }
{ run: 42, event: 4 }
{ run: 42, event: 5 }
{ run: 42, event: 6 }
{ run: 42, event: 7 }
{ run: 42, event: 8 }
{ run: 42, event: 9 }
```

### Solution?
Writing a custom version of "CloneTree" using the root branches rather than the leaf branches appears
to be working. Now need to check all of the details.
- [ ] what about fundamental type branches (BSILFD) that ROOT does not use `TBranchElement` for
- [ ] what about `std::vector` branches
- [ ] what about `std::map` branches
- [ ] what if the dictionary for an object is not available?
