#include "core/transform.hpp"
#include "graphics/data.hpp"
#include "math/constants.hpp"
#include "math/matrix4.hpp"
#include "math/vector2.hpp"
#include <graphics/renderer.hpp>

#include <core/debug.hpp>
#include <graphics/gl.hpp>

#define MAX_INSTANCES 10000

namespace gl = Lux::Graphics::gl;

Lux::Graphics::Renderer::Renderer()
    : default_shader_("src/shaders/default.vert", "src/shaders/default.frag")
{
    default_shader_.use();
    default_shader_.set_uniform_matrix4f(Lux::Math::Matrix4::ortho(0,800,800,0,-1.0f,1.0f), "u_Projection");

    transform_instances_.set_capacity(sizeof(Math::Matrix4) * MAX_INSTANCES);

    vao.bind();
    vao.set_location_format(0, VertexType::Float32, 3, 0);
    vao.set_location_binding(0, 0);

    vao.set_location_format(1, VertexType::Float32, 3, 3);
    vao.set_location_binding(1, 0);

    vao.set_location_format(2, VertexType::Float32, 2, 6);
    vao.set_location_binding(2, 0);

    vao.set_location_format(3, VertexType::Float32, 4, 0);
    vao.set_location_format(4, VertexType::Float32, 4, 4);
    vao.set_location_format(5, VertexType::Float32, 4, 8);
    vao.set_location_format(6, VertexType::Float32, 4, 12);

    vao.set_location_binding(3, 1);
    vao.set_location_binding(4, 1);
    vao.set_location_binding(5, 1);
    vao.set_location_binding(6, 1);

    vao.set_binding_divisor(1, 1);

    setup_default_meshes();

    gl::ClearColor(0,0,0,1);
}

Lux::Graphics::Renderer::~Renderer() = default;

void Lux::Graphics::Renderer::setup_default_meshes(){
    //quad
    VertexData vertices[] = {
        0.0,0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        1, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
         1, 1, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0,
         0,1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0
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

void Lux::Graphics::Renderer::begin(){
    gl::Clear(GL_COLOR_BUFFER_BIT);
}

void Lux::Graphics::Renderer::submit(){
    RenderRequest* linked = nullptr;
    for(RenderRequest& rr : render_queue){
        if(linked != &rr){
            vao.link_vbo(rr.mesh->get_vbo(), sizeof(VertexData), 0);
            vao.link_ebo(rr.mesh->get_ebo());

            linked = &rr;
        }

        transform_instances_.submit_data(rr.transform_instances.data(), rr.transform_instances.size() * sizeof(Math::Matrix4), 0);

        vao.link_vbo(transform_instances_, sizeof(Math::Matrix4), 1);

        gl::DrawElementsInstanced(GL_TRIANGLES, rr.mesh->get_index_count(), GL_UNSIGNED_INT, nullptr, rr.count);
    }

    render_queue.clear();
}

void Lux::Graphics::Renderer::add_to_queue(Graphics::Mesh* mesh, Core::Transform& transform){
    RenderRequest render_request = {};

    bool found = false;

    for(RenderRequest& rr : render_queue){
        if(rr.mesh == mesh){
            rr.count++;
            rr.transform_instances.push_back(transform.get_matrix());
            found = true;
            break;
        }
    }

    if(!found){
        RenderRequest rr;
        rr.mesh = mesh;
        rr.transform_instances.push_back(transform.get_matrix());
        rr.count = 1;
        render_queue.push_back(rr);
    }
}

void Lux::Graphics::Renderer::draw_rect(Math::Vector2 position, u32 width, u32 height, f32 rotation){
    Core::Transform transform;

    rotation = Math::to_radians(rotation);

    transform.set_position(Math::Vector3{position.x, position.y, 0.0f});
    transform.set_scale(Math::Vector3{(f32)width, (f32)height, 1.0f});
    transform.set_rotation({0, 0, rotation});

    add_to_queue(&quad_, transform);
}