#include <graphics/mesh.hpp>

i32 Lux::Graphics::Mesh::next_id = 0;
std::vector<i32> Lux::Graphics::Mesh::free_index_list;

Lux::Graphics::Mesh::Mesh()
    : id(Mesh::assign_id())
{}

void Lux::Graphics::Mesh::set_vertices_capacity(size_t size){
    vertices_vbo_.set_capacity(size);
}

void Lux::Graphics::Mesh::set_indices_capacity(size_t size){
    indices_ebo_.set_capacity(size);
}

void Lux::Graphics::Mesh::set_vertices(VertexData* vertices, u32 count){
    size_t bytes = sizeof(VertexData) * count;
    if(bytes <= vertices_vbo_.get_capacity())
        vertices_vbo_.submit_data(vertices, bytes, 0);
}

void Lux::Graphics::Mesh::set_indices(IndexData* indices, u32 count){
    size_t bytes = sizeof(IndexData) * count;
    index_count_ = count;
    if(bytes <= indices_ebo_.get_capacity()){
        indices_ebo_.submit_data(indices, bytes, 0);
        index_count_= count;
    }
}

const Lux::Graphics::VBO& Lux::Graphics::Mesh::get_vbo(){
    return vertices_vbo_;
}

const Lux::Graphics::EBO& Lux::Graphics::Mesh::get_ebo(){
    return indices_ebo_;
}

u32 Lux::Graphics::Mesh::get_index_count(){
    return index_count_;
}

i32 Lux::Graphics::Mesh::assign_id(){
    i32 id;
    
    if(free_index_list.size() != 0){
        id = free_index_list.back();
        free_index_list.pop_back();

    }else{
        id = next_id;
        next_id++;
    }

    return id;
}