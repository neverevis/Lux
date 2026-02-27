#include <core/log.hpp>
#include <graphics/resource_manager.hpp>

Lux::Graphics::ResourceManager::ResourceManager(u32 mesh_limit)
    : mesh_data{
        mesh_limit,
        std::vector<bool>(mesh_limit,false),
        mesh_limit * sizeof(Mesh),
        0,
        std::vector<u32>()
    }
{
    meshes = (Mesh*) malloc(mesh_limit * sizeof(Mesh));
}

Lux::Graphics::ResourceManager::~ResourceManager(){
    unload_all_meshes();
    free(meshes);
}

u32 Lux::Graphics::ResourceManager::load_mesh(VertexData* vertices_data, IndexData* indices_data, u32 vertices_count, u32 indices_count){
    u32 id;
    if(mesh_data.free_id_.empty()){
        if(mesh_data.next_id_ < mesh_data.limit_){
            id = mesh_data.next_id_;
            mesh_data.next_id_++;
        }
        else{
            LUX_ERROR("no space to store new meshes");
            return -1;
        }
    }else{
        id = mesh_data.free_id_.back();
        mesh_data.free_id_.pop_back();
    }

    new (&meshes[id]) Mesh();

    mesh_data.occupancy_[id] = true;

    meshes[id].set_vertices_capacity(vertices_count * sizeof(VertexData));
    meshes[id].set_indices_capacity(indices_count * sizeof(IndexData));
    meshes[id].set_vertices(vertices_data, vertices_count);
    meshes[id].set_indices(indices_data, indices_count);

    LUX_INFO("mesh successfuly loaded.");

    return id;
}

void Lux::Graphics::ResourceManager::unload_mesh(u32 mesh_id){
    if(mesh_id < mesh_data.limit_ && mesh_data.occupancy_[mesh_id]){
        meshes[mesh_id].~Mesh();
        mesh_data.occupancy_[mesh_id] = false;

        mesh_data.free_id_.push_back(mesh_id);
    }
}

void Lux::Graphics::ResourceManager::unload_all_meshes(){
    for(int i = 0; i < mesh_data.limit_; i++){
        if(mesh_data.occupancy_[i]){
            meshes[i].~Mesh();
            mesh_data.next_id_ = 0;
            mesh_data.free_id_.clear();

            LUX_INFO("all meshes unloaded");
        }
    }
}