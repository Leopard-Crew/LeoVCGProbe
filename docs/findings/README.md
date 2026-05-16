# LeoVCGProbe Findings

This directory contains verified Leopard/PPC findings for unmodified VCGlib under the LeoVCGProbe build harness.

## Findings

- `LVCP-FIND-0001-vcglib-minimal-mesh-gcc10.md`
  - Minimal mesh baseline.

- `LVCP-FIND-0002-vcglib-triangle-bbox-gcc10.md`
  - In-memory triangle and bounding box.

- `LVCP-FIND-0003-vcglib-normals-gcc10.md`
  - Face and vertex normals.

- `LVCP-FIND-0004-vcglib-ply-write-gcc10.md`
  - ASCII PLY export.

- `LVCP-FIND-0005-vcglib-ply-read-gcc10.md`
  - ASCII PLY import.

- `LVCP-FIND-0006-vcglib-ply-roundtrip-gcc10.md`
  - ASCII PLY write/read roundtrip.

- `LVCP-FIND-0007-vcglib-stl-roundtrip-gcc10.md`
  - ASCII STL write/read roundtrip.

- `LVCP-FIND-0008-vcglib-binary-stl-roundtrip-gcc10.md`
  - Binary STL write/read roundtrip with PPC endian warning.

## Baseline summary

See:

- `../LEOPARD-VCGLIB-BASELINE.md`
