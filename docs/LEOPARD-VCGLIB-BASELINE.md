# Leopard VCGlib Baseline

## Purpose

LeoVCG verifies whether unmodified VCGlib can be used as a practical mesh-processing baseline on Mac OS X Leopard 10.5.8 / PowerPC.

This project does not port or patch VCGlib.

VCGlib is kept under `vendor/vcglib` and remains unchanged.

## Tested system

- Mac OS X Leopard 10.5.8
- PowerPC G5
- GCC 10.5.0
- GCC10 toolchain location:
  `/Users/admin/Desktop/Projekte/_helpers/toolchains/gcc10-bootstrap`

## Toolchain policy

GCC10 is used only as a quarantined C/C++ specialist compiler.

It is not used for:

- Objective-C
- Objective-C++
- Foundation
- AppKit
- Cocoa application code

Leopard-native Cocoa work remains Xcode 3.1.4 / system compiler territory.

## Build policy

All probe binaries are built with:

```text
-static-libstdc++ -static-libgcc
````

This avoids runtime dependencies on `/opt/local` or MacPorts GCC libraries.

Eigen vectorization is disabled for the scalar Leopard/PPC baseline:

```text
-DEIGEN_DONT_VECTORIZE
-DEIGEN_DONT_ALIGN_STATICALLY
-DEIGEN_MAX_ALIGN_BYTES=0
```

This avoids Eigen entering PowerPC/AltiVec paths that currently expect unsupported or unsuitable vector features on this setup.

## Vendor policy

No files under `vendor/` are modified.

All Leopard/PPC-specific behavior is expressed outside `vendor/` through:

- `build-gcc10.sh`
    
- probe sources under `src/`
    
- findings under `docs/findings/`
    

## Confirmed findings

### FIND-0001

Minimal VCGlib mesh type compiles and runs.

### FIND-0002

In-memory triangle mesh and bounding box computation work.

### FIND-0003

Face and vertex normal computation works.

### FIND-0004

ASCII PLY export works.

### FIND-0005

ASCII PLY import works.

### FIND-0006

ASCII PLY write/read roundtrip works.

### FIND-0007

ASCII STL write/read roundtrip works.

### FIND-0008

Binary STL write/read roundtrip works locally on PowerPC, but exported binary STL appears to use host-endian / big-endian byte order.

Binary STL export is therefore not accepted as a portable output path yet.

ASCII STL remains the safe portable STL path.

## Baseline decision

VCGlib is accepted as a usable Leopard/PPC scalar C++ mesh baseline for:

- basic mesh structure
    
- vertices and faces
    
- bounding boxes
    
- face normals
    
- vertex normals
    
- ASCII PLY I/O
    
- ASCII STL I/O
    
- local binary STL roundtrip with endian warning
    

## Restrictions

The following are not yet accepted:

- portable binary STL export
    
- Eigen/AltiVec vectorized path
    
- Objective-C++ integration via GCC10
    
- full upstream CMake build
    
- Qt/OpenGL/Embree/app builds
    
- decimation
    
- repair/cleaning operations
    

## Next phase

A future phase may test:

1. duplicate vertex handling
    
2. degenerate face detection/removal
    
3. basic mesh cleaning
    
4. decimation
    
5. endian-safe binary STL wrapper
    
6. possible LeoMeshKit extraction  
    

