# LVCP-FIND-0004: VCGlib PLY write probe on Leopard/PPC with GCC10

## Date

2026-05-16

## System

- Mac OS X Leopard 10.5.8
- PowerPC G5
- GCC 10.5.0 from quarantined helper toolchain:
  `/Users/admin/Desktop/Projekte/_helpers/toolchains/gcc10-bootstrap`

## Scope

This finding verifies whether VCGlib can export a simple in-memory triangle mesh to an ASCII PLY file on Leopard/PPC.

## Source layout

- Vendored source: `vendor/vcglib`
- Probe source: `src/vcg_ply_write_probe.cpp`
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
LeoVCG PLY write probe ran.
Exporter result: 0
Output path: build/vcg_triangle_write_probe.ply
PLY write check: OK
```

## Generated PLY output

```text
ply
format ascii 1.0
comment VCGLIB generated
element vertex 3
property float x
property float y
property float z
element face 1
property list uchar int vertex_indices
end_header
0 0 0 
1 0 0 
0 1 0 
3 0 1 2 
```

## Runtime dependencies

```text
build/vcg_ply_write_probe:
    /usr/lib/libSystem.B.dylib
```

## Vendor policy

No files under `vendor/` were modified.

## Decision

VCGlib successfully exports a simple triangle mesh to ASCII PLY on Leopard/PPC with the quarantined GCC10 scalar baseline.

Next probes:

1. PLY read
    
2. PLY write/read roundtrip
    
3. STL write/read
    
4. cleaning functions
    
5. decimation  
    

