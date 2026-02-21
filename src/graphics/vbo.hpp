#pragma once

#include <graphics/gl.hpp>
#include <vector>

namespace Lux{
    class VBO{
    public:
        VBO(std::vector<float>& vertices);
        ~VBO();

    private:
        GLuint id_;
    };
}