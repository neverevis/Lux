#pragma once

#include <graphics/opengl/gl.hpp>
#include <graphics/opengl/vbo.hpp>
#include <graphics/opengl/ebo.hpp>

namespace Lux::Graphics::OpenGL{
    class VAO{
    public:
        VAO();
        ~VAO();

        void bind();

        void link_vbo(VBO& vbo, size_t stride, GLint binding_index);
        void link_ebo(EBO& ebo);
        void location_format(GLint location, GLenum type, GLuint quantity);
        void set_location_binding(GLint location ,GLint binding_index);
        void set_binding_divisor(GLint binding_index, GLuint divisor);

    private:
        GLuint id_;
    };
}