#include "graphics/opengl/gl.hpp"
#include <graphics/renderer2D.hpp>
#include <graphics/opengl/vbo.hpp>
#include <graphics/opengl/ebo.hpp>
#include <graphics/opengl/vao.hpp>
#include <graphics/opengl/shader.hpp>

#include <core/debug.hpp>
#include <memory>

#define INSTANCE_QUEUE_SIZE 20000 * 4

namespace gl = Lux::Graphics::OpenGL::gl;

struct Lux::Graphics::Renderer2D::Impl{
    Lux::Graphics::OpenGL::Shader default_shader;

    Lux::Graphics::OpenGL::VBO quad_vbo;
    Lux::Graphics::OpenGL::EBO quad_ebo;
    Lux::Graphics::OpenGL::VAO vao;

    Lux::Graphics::OpenGL::VBO instancing_vbo;

    Impl()
        : default_shader("src/shaders/a.vert","src/shaders/a.frag")
    {}
};

Lux::Graphics::Renderer2D::Renderer2D()
    : impl_(std::make_unique<Impl>())
{
    instance_queue.reserve(INSTANCE_QUEUE_SIZE);
    //setting up quads VBO/EBO for 2D rendering
    f32 quad_vertices[] = {
        -0.2, -0.2,
        -0.2,  0.2,
         0.2,  0.2,
         0.2, -0.2
    };

    u32 quad_indices[] = {
        0,1,2,
        2,3,0
    };

    impl_->quad_vbo.set_size(sizeof(quad_vertices));
    impl_->quad_ebo.set_size(sizeof(quad_indices));
    impl_->quad_vbo.submit_data(quad_vertices, sizeof(quad_vertices), 0);
    impl_->quad_ebo.submit_data(quad_indices, sizeof(quad_indices), 0);

    //set instancing vbo size limit
    impl_->instancing_vbo.set_size(INSTANCE_QUEUE_SIZE);

    //linking quad VBO and EBO to VAO and setting on the binding index 0
    impl_->vao.link_vbo(impl_->quad_vbo, 2 * 4, 0);
    impl_->vao.link_ebo(impl_->quad_ebo);

    //linking instancing VBO and setting on the binding index 1
    impl_->vao.link_vbo(impl_->instancing_vbo, 2 * 4, 1);

    //quad location format and binding
    impl_->vao.location_format(0, GL_FLOAT, 2);
    impl_->vao.set_location_binding(0, 0);

    //instancing location format and binding
    impl_->vao.location_format(1, GL_FLOAT, 2);
    impl_->vao.set_location_binding(1, 1);

    //set the binding index 1 for instancing
    impl_->vao.set_binding_divisor(1, 1);

    impl_->vao.bind();
    impl_->default_shader.use();

    Lux::Graphics::OpenGL::gl::ClearColor(1,1,1,1);
}

Lux::Graphics::Renderer2D::~Renderer2D(){

}

void Lux::Graphics::Renderer2D::render_quad(f32 x, f32 y){
    add_to_queue(x, y);
}

void Lux::Graphics::Renderer2D::add_to_queue(f32 x, f32 y){
    instance_queue.push_back(x);
    instance_queue.push_back(y);
}

void Lux::Graphics::Renderer2D::begin(){
    gl::Clear(GL_COLOR_BUFFER_BIT);
}

void convert_to_ndc(std::vector<f32>& values){
    for(f32& v : values){
        v = (v * 2 / 800) - 1;
    }
}

void Lux::Graphics::Renderer2D::submit(){
    u32 instances = instance_queue.size()/2;

    convert_to_ndc(instance_queue);

    impl_->instancing_vbo.submit_data(instance_queue.data(), instance_queue.size() * sizeof(f32), 0);
    instance_queue.clear();

    gl::DrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, instances);
}