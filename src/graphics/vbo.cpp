#include <graphics/vbo.hpp>

Lux::Graphics::VBO::VBO(){
    gl::CreateBuffers(1, &id_);
}

Lux::Graphics::VBO::~VBO(){
    if(id_ != 0)
        gl::DeleteBuffers(1, &id_);
}

void Lux::Graphics::VBO::set_capacity(size_t size){
    if(!stored_){
        stored_ = true;
        capacity_ = size;
        gl::NamedBufferStorage(id_, size, nullptr, GL_DYNAMIC_STORAGE_BIT);
    }
}

void Lux::Graphics::VBO::submit_data(const void* data, size_t size, size_t offset){
    if(stored_ && (size + offset) <= capacity_){
        gl::NamedBufferSubData(id_, offset, size, data);
    }
}

size_t Lux::Graphics::VBO::get_capacity(){
    return capacity_;
}
