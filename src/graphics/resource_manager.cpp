#include <core/log.hpp>
#include <graphics/resource_manager.hpp>

Lux::Graphics::ResourceManager::ResourceManager(u32 mesh_limit)
    : mesh_pool(mesh_limit)
{}

Lux::Graphics::ResourceManager::~ResourceManager(){}

u32 Lux::Graphics::ResourceManager::load_mesh(VertexData* vertices_data, IndexData* indices_data, u32 vertices_count, u32 indices_count){
    u32 id = mesh_pool.add();

    mesh_pool[id].set_vertices_capacity(vertices_count * sizeof(VertexData));
    mesh_pool[id].set_indices_capacity(indices_count * sizeof(IndexData));
    mesh_pool[id].set_vertices(vertices_data, vertices_count);
    mesh_pool[id].set_indices(indices_data, indices_count);

    LUX_INFO("mesh successfuly loaded.");

    return id;
}

Lux::Graphics::Mesh& Lux::Graphics::ResourceManager::get_mesh(u32 mesh_id){
    if(mesh_pool.is_active(mesh_id)){
        return mesh_pool[mesh_id];
    }
    else{
        LUX_ERROR("cannot get invalid mesh id");
    }
}

void Lux::Graphics::ResourceManager::unload_mesh(u32 mesh_id){
    mesh_pool.remove(mesh_id);
}

void Lux::Graphics::ResourceManager::unload_all_meshes(){
    mesh_pool.clear();
}