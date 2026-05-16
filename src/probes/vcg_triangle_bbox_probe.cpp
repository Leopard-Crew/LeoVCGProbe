#include <iostream>
#include <vector>

#include <vcg/complex/complex.h>
#include <vcg/complex/algorithms/update/bounding.h>

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

int main()
{
    LeoMesh mesh;

    vcg::tri::Allocator<LeoMesh>::AddVertices(mesh, 3);
    vcg::tri::Allocator<LeoMesh>::AddFaces(mesh, 1);

    mesh.vert[0].P() = vcg::Point3f(0.0f, 0.0f, 0.0f);
    mesh.vert[1].P() = vcg::Point3f(1.0f, 0.0f, 0.0f);
    mesh.vert[2].P() = vcg::Point3f(0.0f, 2.0f, 3.0f);

    mesh.face[0].V(0) = &mesh.vert[0];
    mesh.face[0].V(1) = &mesh.vert[1];
    mesh.face[0].V(2) = &mesh.vert[2];

    vcg::tri::UpdateBounding<LeoMesh>::Box(mesh);

    std::cout << "LeoVCG triangle bounding box probe ran." << std::endl;
    std::cout << "Vertices: " << mesh.vert.size() << std::endl;
    std::cout << "Faces: " << mesh.face.size() << std::endl;

    printPoint("Bounding box min", mesh.bbox.min);
    printPoint("Bounding box max", mesh.bbox.max);

    return 0;
}
