#include <graphics/opengl/gl.hpp>
#include <graphics/opengl/ebo.hpp>

Lux::Graphics::OpenGL::EBO::EBO(){
    gl::CreateBuffers(1, &id_);
}

Lux::Graphics::OpenGL::EBO::~EBO(){
    if(id_ != 0)
        gl::DeleteBuffers(1, &id_);
}

void Lux::Graphics::OpenGL::EBO::set_size(size_t size){
    if(!stored_){
        stored_ = true;
        size_ = size;
        gl::NamedBufferStorage(id_, size, nullptr, GL_DYNAMIC_STORAGE_BIT);
    }
}

void Lux::Graphics::OpenGL::EBO::submit_data(const void* data, size_t size, size_t offset){
    if(stored_ && (size + offset) <= size_){
        gl::NamedBufferSubData(id_, offset, size, data);
    }
}