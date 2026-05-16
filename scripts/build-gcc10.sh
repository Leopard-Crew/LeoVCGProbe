#!/bin/sh
set -e

. /Users/admin/Desktop/Projekte/_helpers/toolchains/use-gcc10.sh

VCGLIB="vendor/vcglib"

mkdir -p build

COMMON_FLAGS="-std=c++17 $LEOPARD_GCC10_STATIC_FLAGS -DEIGEN_DONT_VECTORIZE -DEIGEN_DONT_ALIGN_STATICALLY -DEIGEN_MAX_ALIGN_BYTES=0"
COMMON_INCLUDES="-I$VCGLIB -I$VCGLIB/eigenlib"
PLYLIB="$VCGLIB/wrap/ply/plylib.cpp"

echo "Building minimal mesh probe..."
g++ $COMMON_FLAGS $COMMON_INCLUDES \
    src/probes/vcg_minimal_probe.cpp \
    -o build/vcg_minimal_probe

echo "Building triangle bounding box probe..."
g++ $COMMON_FLAGS $COMMON_INCLUDES \
    src/probes/vcg_triangle_bbox_probe.cpp \
    -o build/vcg_triangle_bbox_probe

echo "Building normals probe..."
g++ $COMMON_FLAGS $COMMON_INCLUDES \
    src/probes/vcg_normals_probe.cpp \
    -o build/vcg_normals_probe

echo "Building PLY write probe..."
g++ $COMMON_FLAGS $COMMON_INCLUDES \
    src/probes/vcg_ply_write_probe.cpp \
    "$PLYLIB" \
    -o build/vcg_ply_write_probe

echo "Building PLY read probe..."
g++ $COMMON_FLAGS $COMMON_INCLUDES \
    src/probes/vcg_ply_read_probe.cpp \
    "$PLYLIB" \
    -o build/vcg_ply_read_probe

echo "Building PLY roundtrip probe..."
g++ $COMMON_FLAGS $COMMON_INCLUDES \
    src/probes/vcg_ply_roundtrip_probe.cpp \
    "$PLYLIB" \
    -o build/vcg_ply_roundtrip_probe

echo "Building STL ASCII roundtrip probe..."
g++ $COMMON_FLAGS $COMMON_INCLUDES \
    src/probes/vcg_stl_roundtrip_probe.cpp \
    -o build/vcg_stl_roundtrip_probe

echo "Building STL binary roundtrip probe..."
g++ $COMMON_FLAGS $COMMON_INCLUDES \
    src/probes/vcg_stl_binary_roundtrip_probe.cpp \
    -o build/vcg_stl_binary_roundtrip_probe

echo "Running minimal mesh probe..."
./build/vcg_minimal_probe

echo "Running triangle bounding box probe..."
./build/vcg_triangle_bbox_probe

echo "Running normals probe..."
./build/vcg_normals_probe

echo "Running PLY write probe..."
./build/vcg_ply_write_probe

echo "PLY output header:"
head -20 build/vcg_triangle_write_probe.ply

echo "Running PLY read probe..."
./build/vcg_ply_read_probe

echo "Running PLY roundtrip probe..."
./build/vcg_ply_roundtrip_probe

echo "Running STL ASCII roundtrip probe..."
./build/vcg_stl_roundtrip_probe

echo "STL ASCII output preview:"
head -20 build/vcg_triangle_roundtrip_probe.stl

echo "Running STL binary roundtrip probe..."
./build/vcg_stl_binary_roundtrip_probe

echo "STL binary header/count preview:"
od -An -tx1 -N 96 build/vcg_triangle_binary_roundtrip_probe.stl

echo "Runtime dependencies:"
otool -L build/vcg_minimal_probe
otool -L build/vcg_triangle_bbox_probe
otool -L build/vcg_normals_probe
otool -L build/vcg_ply_write_probe
otool -L build/vcg_ply_read_probe
otool -L build/vcg_ply_roundtrip_probe
otool -L build/vcg_stl_roundtrip_probe
otool -L build/vcg_stl_binary_roundtrip_probe
