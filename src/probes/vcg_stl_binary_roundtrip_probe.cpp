#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include <vcg/complex/complex.h>
#include <vcg/complex/algorithms/update/bounding.h>
#include <vcg/complex/algorithms/update/normal.h>
#include <wrap/io_trimesh/io_mask.h>
#include <wrap/io_trimesh/export_stl.h>
#include <wrap/io_trimesh/import_stl.h>

class LeoVertex;
class LeoFace;

struct LeoUsedTypes : public vcg::UsedTypes<
    vcg::Use<LeoVertex>::AsVertexType,
    vcg::Use<LeoFace>::AsFaceType
> {};

class LeoVertex : public vcg::Vertex<
    LeoUsedTypes,
    vcg::vertex::Coord3f,
    vcg::vertex::Normal3f,
    vcg::vertex::BitFlags
> {};

class LeoFace : public vcg::Face<
    LeoUsedTypes,
    vcg::face::VertexRef,
    vcg::face::Normal3f,
    vcg::face::BitFlags
> {};

class LeoMesh : public vcg::tri::TriMesh<
    std::vector<LeoVertex>,
    std::vector<LeoFace>
> {};

static void printPoint(const char *label, const vcg::Point3f &p)
{
    std::cout << label << ": "
              << p.X() << ", "
              << p.Y() << ", "
              << p.Z() << std::endl;
}

static bool nearlyEqual(float a, float b)
{
    const float epsilon = 0.0001f;
    float diff = a - b;
    if (diff < 0.0f) {
        diff = -diff;
    }
    return diff <= epsilon;
}

static bool pointEquals(const vcg::Point3f &p, float x, float y, float z)
{
    return nearlyEqual(p.X(), x)
        && nearlyEqual(p.Y(), y)
        && nearlyEqual(p.Z(), z);
}

static bool getFileSize(const char *path, long &sizeOut)
{
    std::ifstream in(path, std::ios::binary | std::ios::ate);
    if (!in) {
        return false;
    }

    sizeOut = static_cast<long>(in.tellg());
    return true;
}

static bool readBinaryStlTriangleCounts(const char *path, unsigned long &littleEndianOut, unsigned long &bigEndianOut)
{
    unsigned char headerAndCount[84];

    std::ifstream in(path, std::ios::binary);
    if (!in) {
        return false;
    }

    in.read(reinterpret_cast<char *>(headerAndCount), sizeof(headerAndCount));
    if (in.gcount() != static_cast<std::streamsize>(sizeof(headerAndCount))) {
        return false;
    }

    littleEndianOut =
        static_cast<unsigned long>(headerAndCount[80])
        | (static_cast<unsigned long>(headerAndCount[81]) << 8)
        | (static_cast<unsigned long>(headerAndCount[82]) << 16)
        | (static_cast<unsigned long>(headerAndCount[83]) << 24);

    bigEndianOut =
        (static_cast<unsigned long>(headerAndCount[80]) << 24)
        | (static_cast<unsigned long>(headerAndCount[81]) << 16)
        | (static_cast<unsigned long>(headerAndCount[82]) << 8)
        | static_cast<unsigned long>(headerAndCount[83]);

    return true;
}

static void buildSourceMesh(LeoMesh &mesh)
{
    vcg::tri::Allocator<LeoMesh>::AddVertices(mesh, 3);
    vcg::tri::Allocator<LeoMesh>::AddFaces(mesh, 1);

    mesh.vert[0].P() = vcg::Point3f(0.0f, 0.0f, 0.0f);
    mesh.vert[1].P() = vcg::Point3f(1.0f, 0.0f, 0.0f);
    mesh.vert[2].P() = vcg::Point3f(0.0f, 1.0f, 0.0f);

    mesh.face[0].V(0) = &mesh.vert[0];
    mesh.face[0].V(1) = &mesh.vert[1];
    mesh.face[0].V(2) = &mesh.vert[2];

    vcg::tri::UpdateNormal<LeoMesh>::PerVertexNormalizedPerFaceNormalized(mesh);
    vcg::tri::UpdateBounding<LeoMesh>::Box(mesh);
}

int main()
{
    const char *roundtripPath = "build/vcg_triangle_binary_roundtrip_probe.stl";

    LeoMesh sourceMesh;
    LeoMesh importedMesh;

    buildSourceMesh(sourceMesh);

    const int exportErr =
        vcg::tri::io::ExporterSTL<LeoMesh>::Save(sourceMesh, roundtripPath, true);

    int loadMask = 0;
    const int importErr =
        vcg::tri::io::ImporterSTL<LeoMesh>::Open(importedMesh, roundtripPath, loadMask);

    std::cout << "LeoVCG binary STL roundtrip probe ran." << std::endl;
    std::cout << "Export result: " << exportErr << std::endl;
    std::cout << "Import result: " << importErr << std::endl;
    std::cout << "Load mask: " << loadMask << std::endl;
    std::cout << "Roundtrip path: " << roundtripPath << std::endl;

    if (exportErr != 0) {
        std::cerr << "ERROR: binary STL export failed" << std::endl;
        return 1;
    }

    if (importErr != 0) {
        std::cerr << "ERROR: binary STL import failed" << std::endl;
        return 1;
    }

    long fileSize = 0;
    unsigned long triangleCountLE = 0;
    unsigned long triangleCountBE = 0;

    if (!getFileSize(roundtripPath, fileSize)) {
        std::cerr << "ERROR: could not read binary STL file size" << std::endl;
        return 1;
    }

    if (!readBinaryStlTriangleCounts(roundtripPath, triangleCountLE, triangleCountBE)) {
        std::cerr << "ERROR: could not read binary STL triangle count" << std::endl;
        return 1;
    }

    std::cout << "Binary STL file size: " << fileSize << std::endl;
    std::cout << "Binary STL triangle count LE: " << triangleCountLE << std::endl;
    std::cout << "Binary STL triangle count BE: " << triangleCountBE << std::endl;

    if (fileSize != 134) {
        std::cerr << "ERROR: unexpected binary STL file size" << std::endl;
        return 1;
    }

    if (triangleCountLE == 1) {
        std::cout << "Binary STL endian check: little-endian standard count OK" << std::endl;
    } else if (triangleCountBE == 1) {
        std::cout << "Binary STL endian check: WARNING PPC big-endian triangle count observed" << std::endl;
    } else {
        std::cerr << "ERROR: unexpected binary STL triangle count in both endian interpretations" << std::endl;
        return 1;
    }

    vcg::tri::UpdateBounding<LeoMesh>::Box(importedMesh);

    std::cout << "Imported vertices: " << importedMesh.vert.size() << std::endl;
    std::cout << "Imported faces: " << importedMesh.face.size() << std::endl;

    printPoint("Imported bounding box min", importedMesh.bbox.min);
    printPoint("Imported bounding box max", importedMesh.bbox.max);

    if (importedMesh.vert.size() != 3 || importedMesh.face.size() != 1) {
        std::cerr << "ERROR: unexpected mesh size after binary STL roundtrip" << std::endl;
        return 1;
    }

    if (!pointEquals(importedMesh.bbox.min, 0.0f, 0.0f, 0.0f)
        || !pointEquals(importedMesh.bbox.max, 1.0f, 1.0f, 0.0f)) {
        std::cerr << "ERROR: unexpected bounding box after binary STL roundtrip" << std::endl;
        return 1;
    }

    std::cout << "Binary STL roundtrip check: OK" << std::endl;
    return 0;
}
