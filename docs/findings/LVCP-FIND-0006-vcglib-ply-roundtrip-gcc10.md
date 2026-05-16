# LVCP-FIND-0006: VCGlib PLY roundtrip probe on Leopard/PPC with GCC10

## Date

2026-05-16

## System

- Mac OS X Leopard 10.5.8
- PowerPC G5
- GCC 10.5.0 from quarantined helper toolchain:
  `/Users/admin/Desktop/Projekte/_helpers/toolchains/gcc10-bootstrap`

## Scope

This finding verifies whether VCGlib can export and re-import a simple triangle mesh as ASCII PLY in one closed roundtrip probe on Leopard/PPC.

## Source layout

- Vendored source: `vendor/vcglib`
- Probe source: `src/vcg_ply_roundtrip_probe.cpp`
- Build harness: `build-gcc10.sh`
- Linked VCGlib helper source: `vendor/vcglib/wrap/ply/plylib.cpp`

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
LeoVCG PLY roundtrip probe ran.
Export result: 0
Import result: 0
Roundtrip path: build/vcg_triangle_roundtrip_probe.ply
Imported vertices: 3
Imported faces: 1
Imported bounding box min: 0, 0, 0
Imported bounding box max: 1, 1, 0
PLY roundtrip check: OK
```

## Runtime dependencies

```text
build/vcg_ply_roundtrip_probe:
    /usr/lib/libSystem.B.dylib
```

## Vendor policy

No files under `vendor/` were modified.

## Decision

VCGlib successfully performs an ASCII PLY write/read roundtrip on Leopard/PPC with the quarantined GCC10 scalar baseline.

The PLY path is accepted for further Leopard/PPC exploration.

Next probes:

1. STL write/read
    
2. mesh cleaning functions
    
3. decimation  
    

