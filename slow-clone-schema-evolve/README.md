# Rename a std::map Member Variable

This is test code for a ROOT Forum post.
https://root-forum.cern.ch/t/schema-evolution-renaming-a-std-map-member-variable/64310

I am unable to use the simple `#pragma read` statement to rename a member variable
that has the `std::map` type. In this case, it seems to just be ignored, but in
a more complex case (see LDMX-Software/ldmx-sw Issue #1815) it results in a segmentation
fault.

## Compile
Normal config and build cycle using CMake to find and configure the ROOT installation.
```
cmake -B build -S .
cmake --build build
```

## Run
Write a file using the old version of the Header object and attempt to read that
file with both the old and new versions.

```
./build/write
./build/read-v1
./build/read-v2
```

With the denv inherited from this repository, all of these commands can be run by
prefixing them with `denv` and the exact ldmx-sw environment will be replicated.
```
denv ./show
```
