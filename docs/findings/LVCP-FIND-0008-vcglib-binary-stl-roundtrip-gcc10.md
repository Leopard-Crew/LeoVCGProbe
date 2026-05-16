# LVCP-FIND-0008: VCGlib binary STL roundtrip probe on Leopard/PPC with GCC10

## Date

2026-05-16

## System

- Mac OS X Leopard 10.5.8
- PowerPC G5
- GCC 10.5.0 from quarantined helper toolchain:
  `/Users/admin/Desktop/Projekte/_helpers/toolchains/gcc10-bootstrap`

## Scope

This finding verifies whether VCGlib can export and re-import a simple triangle mesh as binary STL on Leopard/PPC.

This probe also checks the byte order of the binary STL triangle-count field because PowerPC is big-endian.

## Source layout

- Vendored source: `vendor/vcglib`
- Probe source: `src/vcg_stl_binary_roundtrip_probe.cpp`
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
LeoVCG binary STL roundtrip probe ran.
Export result: 0
Import result: 0
Load mask: 65
Roundtrip path: build/vcg_triangle_binary_roundtrip_probe.stl
Binary STL file size: 134
Binary STL triangle count LE: 16777216
Binary STL triangle count BE: 1
Binary STL endian check: WARNING PPC big-endian triangle count observed
Imported vertices: 3
Imported faces: 1
Imported bounding box min: 0, 0, 0
Imported bounding box max: 1, 1, 0
Binary STL roundtrip check: OK
```

## Binary header/count preview

```text
56 43 47 20 20 20 20 20 20 20 20 20 20 20 20 20
20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20
*
00 00 00 01 00 00 00 00 00 00 00 00 3f 80 00 00
```

The triangle-count bytes are:

```text
00 00 00 01
```

Interpreted as little-endian, this is `16777216`.

Interpreted as big-endian, this is `1`.

## Runtime dependencies

```text
build/vcg_stl_binary_roundtrip_probe:
    /usr/lib/libSystem.B.dylib
```

## Vendor policy

No files under `vendor/` were modified.

## Decision

VCGlib can perform a local binary STL export/import roundtrip on Leopard/PPC.

However, the generated binary STL appears to use PowerPC host-endian byte order. Standard binary STL files are expected to use little-endian fields.

Therefore:

- binary STL roundtrip is accepted as a local PPC capability
    
- binary STL export is not accepted as a portable output path yet
    
- ASCII STL remains the safe portable STL output path
    
- a future Leopard-Crew wrapper should write binary STL explicitly in little-endian byte order
    

## Next probes

1. basic cleaning / duplicate vertex handling
    
2. degenerate face handling
    
3. decimation  

