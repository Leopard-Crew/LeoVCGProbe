#include <cmath>
#include <iostream>
#include <vector>

#include <vcg/complex/complex.h>
#include <vcg/complex/algorithms/update/bounding.h>
#include <wrap/io_trimesh/import_ply.h>

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

int main()
{
    const char *inputPath = "build/vcg_triangle_write_probe.ply";

    LeoMesh mesh;

    const int err = vcg::tri::io::ImporterPLY<LeoMesh>::Open(mesh, inputPath);

    std::cout << "LeoVCG PLY read probe ran." << std::endl;
    std::cout << "Importer result: " << err << std::endl;
    std::cout << "Input path: " << inputPath << std::endl;

    if (err != 0) {
        std::cerr << "ERROR: PLY import failed" << std::endl;
        return 1;
    }

    vcg::tri::UpdateBounding<LeoMesh>::Box(mesh);

    std::cout << "Vertices: " << mesh.vert.size() << std::endl;
    std::cout << "Faces: " << mesh.face.size() << std::endl;

    printPoint("Bounding box min", mesh.bbox.min);
    printPoint("Bounding box max", mesh.bbox.max);

    if (mesh.vert.size() != 3 || mesh.face.size() != 1) {
        std::cerr << "ERROR: unexpected mesh size after PLY import" << std::endl;
        return 1;
    }

    if (!pointEquals(mesh.bbox.min, 0.0f, 0.0f, 0.0f)
        || !pointEquals(mesh.bbox.max, 1.0f, 1.0f, 0.0f)) {
        std::cerr << "ERROR: unexpected bounding box after PLY import" << std::endl;
        return 1;
    }

    std::cout << "PLY read check: OK" << std::endl;
    return 0;
}
