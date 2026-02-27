#pragma once

#include <graphics/mesh.hpp>
#include <graphics/data.hpp>

namespace Lux::Graphics{
    class ResourceManager{
    public:
        Mesh* meshes;

        ResourceManager(u32 mesh_limit);
        ~ResourceManager();

        u32 load_mesh(VertexData* vertices_data, IndexData* indices_data, u32 vertices_count, u32 indices_count);

        void unload_mesh(u32 mesh_id);
        void unload_all_meshes();
        
    private:
        struct Data{
            const u32           limit_;
            std::vector<bool>   occupancy_; //actually creates a dynamic bitset
            size_t              capacity_;
            u32                 next_id_;
            std::vector<u32>    free_id_;
        };
        Data mesh_data;
    };
}