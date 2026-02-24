#pragma once

#include <core/types.hpp>
#include <graphics/mesh.hpp>
#include <graphics/shader.hpp>

namespace Lux::Graphics{
    class Renderer{
    public:
        Renderer();
        ~Renderer();

        void begin();
        void submit();
    private:
        Shader default_shader_;
        Mesh quad_;
    };
}