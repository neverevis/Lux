#include <graphics/renderer.hpp>

#include <core/debug.hpp>
#include <graphics/gl.hpp>

#include <iostream>

namespace gl = Lux::Graphics::gl;

Lux::Graphics::Renderer::Renderer()
    : default_shader_("src/shaders/default.vert", "src/shaders/default.frag")
{
    vao.bind();
    vao.set_location_format(0, VertexType::Float32, 3, 0);
    vao.set_location_binding(0, 0);

    vao.set_location_format(1, VertexType::Float32, 3, 3);
    vao.set_location_binding(1, 0);

    vao.set_location_format(2, VertexType::Float32, 2, 6);
    vao.set_location_binding(2, 0);

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

    gl::ClearColor(0,1,0,1);
    default_shader_.use();
}

Lux::Graphics::Renderer::~Renderer() = default;

void Lux::Graphics::Renderer::begin(){
    gl::Disable(GL_CULL_FACE);
    gl::Disable(GL_DEPTH_TEST);
    gl::Clear(GL_COLOR_BUFFER_BIT);
}

void Lux::Graphics::Renderer::submit(){
    for(RenderRequest& r : render_queue){
        vao.link_vbo(r.mesh->get_vbo(), sizeof(VertexData), 0);
        vao.link_ebo(r.mesh->get_ebo());

        gl::DrawElementsInstanced(GL_TRIANGLES, r.mesh->get_index_count(), GL_UNSIGNED_INT, nullptr, r.count);
    }

    render_queue.clear();
    std::cout << "end" << std::endl;
}

void Lux::Graphics::Renderer::add_to_queue(Lux::Graphics::Mesh* mesh){
    RenderRequest render_request = {};

    bool found = false;

    for(RenderRequest& r : render_queue){
        if(r.mesh == mesh){
            r.count++;
            found = true;
            break;
        }
    }

    if(!found){
        RenderRequest rr;
        rr.mesh = mesh;
        rr.count = 1;
        render_queue.push_back(rr);
    }
}

void Lux::Graphics::Renderer::draw_rect(){
    add_to_queue(&quad_);
}