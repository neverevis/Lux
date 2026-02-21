#pragma once

#include <graphics/gl.hpp>

namespace Lux{
    class Shader{
    public:
        Shader(const char* vert_path, const char* frag_path);
        ~Shader();
    private:
        GLint id_;

        void check_shader_errors(GLuint shader);
    };
}