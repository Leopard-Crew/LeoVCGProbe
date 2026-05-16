#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <vcg/complex/complex.h>
#include <vcg/complex/algorithms/update/normal.h>
#include <wrap/io_trimesh/export_ply.h>

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

static bool fileContains(const char *path, const std::string &needle)
{
    std::ifstream in(path);
    if (!in) {
        return false;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.find(needle) != std::string::npos) {
            return true;
        }
    }

    return false;
}

int main()
{
    const char *outputPath = "build/vcg_triangle_write_probe.ply";

    LeoMesh mesh;

    vcg::tri::Allocator<LeoMesh>::AddVertices(mesh, 3);
    vcg::tri::Allocator<LeoMesh>::AddFaces(mesh, 1);

    mesh.vert[0].P() = vcg::Point3f(0.0f, 0.0f, 0.0f);
    mesh.vert[1].P() = vcg::Point3f(1.0f, 0.0f, 0.0f);
    mesh.vert[2].P() = vcg::Point3f(0.0f, 1.0f, 0.0f);

    mesh.face[0].V(0) = &mesh.vert[0];
    mesh.face[0].V(1) = &mesh.vert[1];
    mesh.face[0].V(2) = &mesh.vert[2];

    vcg::tri::UpdateNormal<LeoMesh>::PerVertexNormalizedPerFaceNormalized(mesh);

    const int err = vcg::tri::io::ExporterPLY<LeoMesh>::Save(mesh, outputPath, false);

    std::cout << "LeoVCGProbe PLY write probe ran." << std::endl;
    std::cout << "Exporter result: " << err << std::endl;
    std::cout << "Output path: " << outputPath << std::endl;

    if (err != 0) {
        std::cerr << "ERROR: PLY export failed" << std::endl;
        return 1;
    }

    if (!fileContains(outputPath, "ply")
        || !fileContains(outputPath, "element vertex 3")
        || !fileContains(outputPath, "element face 1")
        || !fileContains(outputPath, "end_header")) {
        std::cerr << "ERROR: PLY output did not contain expected header markers" << std::endl;
        return 1;
    }

    std::cout << "PLY write check: OK" << std::endl;
    return 0;
}
