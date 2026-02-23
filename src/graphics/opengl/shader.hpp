#pragma once

#include <graphics/opengl/gl.hpp>

namespace Lux::Graphics::OpenGL{
    class Shader{
    public:
        Shader(const char* vert_path, const char* frag_path);
        ~Shader();

        void use();
    private:
        GLint id_;

        void check_shader_errors(GLuint shader);
        void check_linking_errors();
    };
}