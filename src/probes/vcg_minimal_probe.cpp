#include <iostream>
#include <vector>

#include <vcg/complex/complex.h>

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

int main()
{
    LeoMesh mesh;

    std::cout << "LeoVCG minimal mesh compiled and ran." << std::endl;
    std::cout << "Vertices: " << mesh.vert.size() << std::endl;
    std::cout << "Faces: " << mesh.face.size() << std::endl;

    return 0;
}
