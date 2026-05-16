# LVCP-FIND-0007: VCGlib STL roundtrip probe on Leopard/PPC with GCC10

## Date

2026-05-16

## System

- Mac OS X Leopard 10.5.8
- PowerPC G5
- GCC 10.5.0 from quarantined helper toolchain:
  `/Users/admin/Desktop/Projekte/_helpers/toolchains/gcc10-bootstrap`

## Scope

This finding verifies whether VCGlib can export and re-import a simple triangle mesh as ASCII STL on Leopard/PPC.

## Source layout

- Vendored source: `vendor/vcglib`
- Probe source: `src/vcg_stl_roundtrip_probe.cpp`
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
LeoVCG STL roundtrip probe ran.
Export result: 0
Import result: 0
Load mask: 65
Roundtrip path: build/vcg_triangle_roundtrip_probe.stl
Imported vertices: 3
Imported faces: 1
Imported bounding box min: 0, 0, 0
Imported bounding box max: 1, 1, 0
STL roundtrip check: OK
```

## Generated ASCII STL output

```text
solid vcg
  facet normal  0.000000e+00  0.000000e+00  1.000000e+00
    outer loop
      vertex   0.000000e+00  0.000000e+00  0.000000e+00
      vertex   1.000000e+00  0.000000e+00  0.000000e+00
      vertex   0.000000e+00  1.000000e+00  0.000000e+00
    endloop
  endfacet
endsolid vcg
```

## Runtime dependencies

```text
build/vcg_stl_roundtrip_probe:
    /usr/lib/libSystem.B.dylib
```

## Vendor policy

No files under `vendor/` were modified.

## Decision

VCGlib successfully performs an ASCII STL write/read roundtrip on Leopard/PPC with the quarantined GCC10 scalar baseline.

This confirms the first 3D-printing-relevant mesh I/O path.

Next probes:

1. STL binary write/read
    
2. mesh cleaning functions
    
3. duplicate vertex removal
    
4. degenerate face detection/removal
    
5. decimation  
    

