#pragma once

#include <graphics/opengl/gl.hpp>

namespace Lux::Graphics::OpenGL{
    class VBO{
    public:
        const GLuint& id = id_;

        VBO();
        ~VBO();

        void set_size(size_t size);
        void submit_data(const void* data, size_t size, size_t offset);

    private:
        GLuint id_ = 0;
        size_t size_;
        bool stored_ = false;
    };
}