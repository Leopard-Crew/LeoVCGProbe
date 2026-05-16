#include <cmath>
#include <iostream>
#include <vector>

#include <vcg/complex/complex.h>
#include <vcg/complex/algorithms/update/normal.h>

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

static bool isExpectedNormal(const vcg::Point3f &p)
{
    return nearlyEqual(p.X(), 0.0f)
        && nearlyEqual(p.Y(), 0.0f)
        && nearlyEqual(p.Z(), 1.0f);
}

int main()
{
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

    std::cout << "LeoVCG normals probe ran." << std::endl;
    std::cout << "Vertices: " << mesh.vert.size() << std::endl;
    std::cout << "Faces: " << mesh.face.size() << std::endl;

    printPoint("Face normal", mesh.face[0].N());
    printPoint("Vertex 0 normal", mesh.vert[0].N());
    printPoint("Vertex 1 normal", mesh.vert[1].N());
    printPoint("Vertex 2 normal", mesh.vert[2].N());

    if (!isExpectedNormal(mesh.face[0].N())
        || !isExpectedNormal(mesh.vert[0].N())
        || !isExpectedNormal(mesh.vert[1].N())
        || !isExpectedNormal(mesh.vert[2].N())) {
        std::cerr << "ERROR: unexpected normal result" << std::endl;
        return 1;
    }

    std::cout << "Normal check: OK" << std::endl;
    return 0;
}
