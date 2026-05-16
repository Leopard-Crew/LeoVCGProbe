# LVCP-FIND-0002: VCGlib triangle and bounding box probe on Leopard/PPC with GCC10

## Date

2026-05-16

## System

- Mac OS X Leopard 10.5.8
- PowerPC G5
- GCC 10.5.0 from quarantined helper toolchain:
  `/Users/admin/Desktop/Projekte/_helpers/toolchains/gcc10-bootstrap`

## Scope

This finding verifies whether VCGlib can manage an in-memory triangle mesh and compute a bounding box on Leopard/PPC.

## Source layout

- Vendored source: `vendor/vcglib`
- Probe source: `src/vcg_triangle_bbox_probe.cpp`
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
LeoVCG triangle bounding box probe ran.
Vertices: 3
Faces: 1
Bounding box min: 0, 0, 0
Bounding box max: 1, 2, 3
```

## Runtime dependencies

```text
build/vcg_triangle_bbox_probe:
    /usr/lib/libSystem.B.dylib
```

## Vendor policy

No files under `vendor/` were modified.

## Decision

VCGlib successfully supports a basic in-memory triangle mesh and bounding box computation on Leopard/PPC with the quarantined GCC10 scalar baseline.

Next probes:

1. face normals
    
2. vertex normals
    
3. PLY write
    
4. PLY read
    
5. STL read/write  
    

