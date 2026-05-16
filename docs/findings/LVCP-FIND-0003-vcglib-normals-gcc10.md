# LVCP-FIND-0003: VCGlib face and vertex normals on Leopard/PPC with GCC10

## Date

2026-05-16

## System

- Mac OS X Leopard 10.5.8
- PowerPC G5
- GCC 10.5.0 from quarantined helper toolchain:
  `/Users/admin/Desktop/Projekte/_helpers/toolchains/gcc10-bootstrap`

## Scope

This finding verifies whether VCGlib can compute face and vertex normals for a simple in-memory triangle mesh on Leopard/PPC.

## Source layout

- Vendored source: `vendor/vcglib`
- Probe source: `src/vcg_normals_probe.cpp`
- Build harness: `build-gcc10.sh`

## Build conditions

Eigen vectorization is disabled in the build harness:

```text
-DEIGEN_DONT_VECTORIZE
-DEIGEN_DONT_ALIGN_STATICALLY
-DEIGEN_MAX_ALIGN_BYTES=0
````

The GCC runtime is linked statically:

```text
-static-libstdc++ -static-libgcc
```

## Runtime result

```text
LeoVCG normals probe ran.
Vertices: 3
Faces: 1
Face normal: 0, 0, 1
Vertex 0 normal: 0, 0, 1
Vertex 1 normal: 0, 0, 1
Vertex 2 normal: 0, 0, 1
Normal check: OK
```

## Runtime dependencies

```text
build/vcg_normals_probe:
    /usr/lib/libSystem.B.dylib
```

## Vendor policy

No files under `vendor/` were modified.

## Decision

VCGlib successfully computes face and vertex normals on Leopard/PPC with the quarantined GCC10 scalar baseline.

Next probes:

1. PLY write
    
2. PLY read
    
3. STL write/read
    
4. cleaning functions
    
5. decimation  

