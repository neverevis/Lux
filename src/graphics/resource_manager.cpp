#include <graphics/resource_manager.hpp>

#define MESH_LIMIT 1024

Lux::Graphics::ResourceManager::ResourceManager(){
    meshes.reserve(sizeof(Mesh) * MESH_LIMIT);
}

u32 Lux::Graphics::ResourceManager::load_mesh(VertexData* vertices_data, IndexData* indices_data, u32 vertices_count, u32 indices_count){
    if(mesh_free_id.size() == 0){
        meshes[mesh_next_id]
    }
}