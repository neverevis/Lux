#pragma once

namespace Lux{
    class Shader{
    public:
        Shader(const char* vert_path, const char* frag_path);
        ~Shader();
    };
}