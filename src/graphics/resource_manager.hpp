#pragma once

#include <graphics/mesh.hpp>
#include <memory/static_pool.hpp>
#include <graphics/data.hpp>

namespace Lux::Graphics{
    class ResourceManager{
    public:
        ResourceManager(u32 mesh_limit);
        ~ResourceManager();

        u32 load_mesh(VertexData* vertices_data, IndexData* indices_data, u32 vertices_count, u32 indices_count);
        Mesh& get_mesh(u32 mesh_id);

        void unload_mesh(u32 mesh_id);
        void unload_all_meshes();
        
    private:
        Memory::StaticPool<Mesh> mesh_pool;
    };
}