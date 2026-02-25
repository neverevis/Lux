#pragma once
#include <core/types.hpp>
#include <math/matrix4.hpp>

namespace Lux::Graphics{
    class Shader{
    public:
        Shader(const char* vert_path, const char* frag_path);
        ~Shader();

        void use();
        void set_uniform_matrix4f(const Lux::Math::Matrix4& matrix4, const char* name);
    private:
        u32 id_;

        void check_shader_errors(u32 shader);
        void check_linking_errors();
    };
}