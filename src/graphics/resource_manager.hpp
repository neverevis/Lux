#pragma once
#include <graphics/mesh.hpp>
#include <graphics/data.hpp>

namespace Lux::Graphics{
    class ResourceManager{
    public:
        std::vector<Mesh> meshes;

        ResourceManager();
        ~ResourceManager();

        u32 load_mesh(VertexData* vertices_data, IndexData* indices_data, u32 vertices_count, u32 indices_count);
    private:
        u32                 mesh_next_id;
        std::vector<u32>    mesh_free_id;
    };
}