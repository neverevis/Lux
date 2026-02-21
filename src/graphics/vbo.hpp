#pragma once

#include <graphics/gl.hpp>
#include <vector>

namespace Lux{
    class VBO{
    public:
        const GLuint& id = id_;

        VBO(std::vector<float>& vertices);
        ~VBO();

    private:
        GLuint id_;
        size_t size_;
    };
}