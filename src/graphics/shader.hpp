#pragma once
#include <core/types.hpp>

namespace Lux::Graphics{
    class Shader{
    public:
        Shader(const char* vert_path, const char* frag_path);
        ~Shader();

        void use();
    private:
        u32 id_;

        void check_shader_errors(u32 shader);
        void check_linking_errors();
    };
}