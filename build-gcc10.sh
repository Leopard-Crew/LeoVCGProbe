#!/bin/sh
set -e

. /Users/admin/Desktop/Projekte/_helpers/toolchains/use-gcc10.sh

VCGLIB="vendor/vcglib"

mkdir -p build

COMMON_FLAGS="-std=c++17 $LEOPARD_GCC10_STATIC_FLAGS -DEIGEN_DONT_VECTORIZE -DEIGEN_DONT_ALIGN_STATICALLY -DEIGEN_MAX_ALIGN_BYTES=0"
COMMON_INCLUDES="-I$VCGLIB -I$VCGLIB/eigenlib"

echo "Building minimal mesh probe..."
g++ $COMMON_FLAGS $COMMON_INCLUDES \
    src/vcg_minimal_probe.cpp \
    -o build/vcg_minimal_probe

echo "Building triangle bounding box probe..."
g++ $COMMON_FLAGS $COMMON_INCLUDES \
    src/vcg_triangle_bbox_probe.cpp \
    -o build/vcg_triangle_bbox_probe

echo "Building normals probe..."
g++ $COMMON_FLAGS $COMMON_INCLUDES \
    src/vcg_normals_probe.cpp \
    -o build/vcg_normals_probe

echo "Running minimal mesh probe..."
./build/vcg_minimal_probe

echo "Running triangle bounding box probe..."
./build/vcg_triangle_bbox_probe

echo "Running normals probe..."
./build/vcg_normals_probe

echo "Runtime dependencies:"
otool -L build/vcg_minimal_probe
otool -L build/vcg_triangle_bbox_probe
otool -L build/vcg_normals_probe
