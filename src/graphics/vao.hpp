#pragma once

#include <graphics/gl.hpp>
#include <graphics/vbo.hpp>

namespace Lux{
    class VAO{
    public:
        const GLuint& id = id_;

        VAO();
        ~VAO();

        void bind();

        void link_vbo(VBO& vbo, size_t vertex_size);
        void set_location(GLuint location, GLint data_type, GLuint size, GLuint offset);

    private:
        GLuint id_;
    };
}