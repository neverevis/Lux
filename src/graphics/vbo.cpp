#include "glcorearb.h"
#include <graphics/vbo.hpp>
#include <graphics/gl.hpp>

Lux::Graphics::VBO::VBO()
    : shared_(false)
    , stored_(false)
    , capacity_(0)
{
    gl::CreateBuffers(1, &id_);
}

Lux::Graphics::VBO::~VBO(){
    if(id_ != 0)
        gl::DeleteBuffers(1, &id_);
}

void Lux::Graphics::VBO::alloc_gpu_memory(size_t size){
    if(!stored_){
        stored_ = true;
        capacity_ = size;
        gl::NamedBufferStorage(id_, size, nullptr, GL_DYNAMIC_STORAGE_BIT);
    }else{
        LUX_VERIFY(false, "can't allocate VBO memory twice");
    }
}

void* Lux::Graphics::VBO::alloc_shared_memory(size_t size){
    if(!stored_){
        shared_ = true;
        stored_ = true;
        capacity_ = size;

        /*
        GL_MAP_WRITE_BIT        ->  indicates that the returned pointer may be used to read buffer object data. 
                                    No GL error is generated if the pointer is used to query a mapping which excludesthis flag,
                                    but the result is undefined and system errors (possibly including program termination) may occur.

        GL_MAP_PERSISTENT_BIT   ->  indicates that the mapping is to be made in a persistent fashion and that the
                                    client intends to hold and use the returned pointer during subsequent GL operation

        GL_MAP_COHERENT_BIT     ->  indicates that a persistent mapping is also to be coherent.
                                    Coherent maps guarantee that the effect of writes to a buffer's data store by
                                    either the client or server will eventually become visible to the other without further
                                    intervention from the application.
        */
        GLbitfield flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;

        gl::NamedBufferStorage(id_, size, nullptr, flags);
        return gl::MapNamedBufferRange(id_, 0, capacity_, flags);
    }

    LUX_VERIFY(false, "can't allocate VBO memory twice");
}

void Lux::Graphics::VBO::submit_data(const void* data, size_t size, size_t offset){
    if(stored_ && (size + offset) <= capacity_ && !shared_){
        gl::NamedBufferSubData(id_, offset, size, data);
    }
}

size_t Lux::Graphics::VBO::get_capacity(){
    return capacity_;
}
