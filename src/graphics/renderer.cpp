#include <graphics/renderer.hpp>

#include <core/debug.hpp>

namespace gl = Lux::Graphics::gl;

Lux::Graphics::Renderer::Renderer()
    : default_shader_("src/shaders/default.vert", "src/shaders/default.frag")
{
    VertexData vertices[] = {
        -0.5,-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        -0.5, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
         0.5, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0,
          0.5,-0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0
    };

    IndexData indices[] = {
        0,1,2,
        2,3,0
    };

    quad_.set_vertices_capacity(sizeof(vertices));
    quad_.set_indices_capacity(sizeof(indices));

    quad_.set_vertices(vertices, 4);
    quad_.set_indices(indices, 6);
}

Lux::Graphics::Renderer::~Renderer() = default;

void Lux::Graphics::Renderer::begin(){
}

void Lux::Graphics::Renderer::submit(){
}