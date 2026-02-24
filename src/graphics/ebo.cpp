#include <graphics/ebo.hpp>

#include <graphics/gl.hpp>

Lux::Graphics::EBO::EBO(){
    gl::CreateBuffers(1, &id_);
}

Lux::Graphics::EBO::~EBO(){
    if(id_ != 0)
        gl::DeleteBuffers(1, &id_);
}

void Lux::Graphics::EBO::set_capacity(size_t size){
    if(!stored_){
        stored_ = true;
        capacity_ = size;
        gl::NamedBufferStorage(id_, size, nullptr, GL_DYNAMIC_STORAGE_BIT);
    }
}

void Lux::Graphics::EBO::submit_data(const void* data, size_t size, size_t offset){
    if(stored_ && (size + offset) <= capacity_){
        gl::NamedBufferSubData(id_, offset, size, data);
    }
}

const size_t Lux::Graphics::EBO::get_capacity(){
    return capacity_;
}