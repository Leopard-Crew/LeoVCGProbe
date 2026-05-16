# LeoVCG

## Leopard/PPC VCGlib baseline

LeoVCG verifies whether unmodified VCGlib can be used on Mac OS X Leopard 10.5.8 / PowerPC.

Current baseline result:

- VCGlib remains unchanged under `vendor/vcglib`.
- GCC10 is used only as a quarantined C/C++ specialist compiler.
- Probe binaries are linked with `-static-libstdc++ -static-libgcc`.
- Runtime dependencies are limited to `/usr/lib/libSystem.B.dylib`.
- Eigen vectorization is disabled for the scalar baseline.
- PLY write/read/roundtrip works.
- ASCII STL write/read/roundtrip works.
- Binary STL roundtrip works locally, but binary STL export appears to be big-endian on PowerPC and is not accepted as a portable output path.

See:

- `docs/LEOPARD-VCGLIB-BASELINE.md`
- `docs/findings/`

