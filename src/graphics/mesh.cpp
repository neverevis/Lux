#include <graphics/mesh.hpp>

void Lux::Graphics::Mesh::set_vertices_capacity(size_t size){
    if(vertices_vbo_size_ == 0)
        vertices_vbo_.set_size(size);
}

void Lux::Graphics::Mesh::set_indices_capacity(size_t size){
    if(indices_ebo_size_ == 0)
        indices_ebo_.set_size(size);
}

void Lux::Graphics::Mesh::set_vertices(VertexData* vertices, u32 count){
    size_t bytes = sizeof(VertexData) * count;
    if(bytes <= vertices_vbo_size_)
        vertices_vbo_.submit_data(vertices, bytes, 0);
}

void Lux::Graphics::Mesh::set_indices(IndexData* indices, u32 count){
    size_t bytes = sizeof(IndexData) * count;
    if(bytes <= indices_ebo_size_){
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