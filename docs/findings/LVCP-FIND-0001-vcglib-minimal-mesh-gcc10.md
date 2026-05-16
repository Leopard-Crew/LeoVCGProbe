# LVCP-FIND-0001: VCGlib minimal mesh baseline on Leopard/PPC with GCC10

## Date

2026-05-16

## System

- Mac OS X Leopard 10.5.8
- PowerPC G5
- GCC 10.5.0 from quarantined helper toolchain:
  `/Users/admin/Desktop/Projekte/_helpers/toolchains/gcc10-bootstrap`

## Scope

This finding verifies whether the vendored VCGlib source tree can be included and compiled from a Leopard/PPC project without modifying files under `vendor/`.

## Source layout

- Project: `LeoVCG`
- Vendored source: `vendor/vcglib`
- Probe source: `src/vcg_minimal_probe.cpp`
- Build harness: `build-gcc10.sh`

## Result

The minimal VCGlib mesh probe builds and runs successfully.

Runtime output:

```text
LeoVCG minimal mesh compiled and ran.
Vertices: 0
Faces: 0
````

`otool -L` output shows only the Leopard system runtime:

```text
build/vcg_minimal_probe:
    /usr/lib/libSystem.B.dylib
```

## Important build condition

Eigen vectorization must be disabled for this first scalar baseline:

```text
-DEIGEN_DONT_VECTORIZE
-DEIGEN_DONT_ALIGN_STATICALLY
-DEIGEN_MAX_ALIGN_BYTES=0
```

Without this, Eigen enters its PowerPC/AltiVec path and fails on this Leopard/PPC/GCC10 setup.

## Vendor policy

No files under `vendor/` were modified.

All Leopard-specific behavior is expressed outside `vendor/`, in the build harness and probe source.

## Decision

VCGlib is accepted for further Leopard/PPC probing as a scalar C++ baseline.

Next probes should remain outside `vendor/` and proceed in this order:

1. create an in-memory triangle
    
2. compute bounding box
    
3. compute face/vertex normals
    
4. test PLY read/write
    
5. test STL read/write
    
6. test cleaning functions
    
7. test decimation  
    

