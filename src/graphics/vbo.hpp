#pragma once

#include <graphics/gl.hpp>

namespace Lux::Graphics{
    class VBO{
    public:
        const GLuint& id = id_;

        VBO();
        ~VBO();

        void alloc_gpu_memory(size_t size);
        void* alloc_shared_memory(size_t size);
        void submit_data(const void* data, size_t size, size_t offset);

        size_t get_capacity();

    private:
        GLuint id_ = 0;
        size_t capacity_;
        bool stored_;
        bool shared_;
    };
}