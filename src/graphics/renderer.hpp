#pragma once

#include "math/matrix4.hpp"
#include <core/types.hpp>
#include <graphics/mesh.hpp>
#include <graphics/shader.hpp>
#include <graphics/vao.hpp>
#include <core/transform.hpp>
#include <math/vector2.hpp>
#include <vector>

namespace Lux::Graphics{
    class Renderer{
        struct RenderRequest{
            Mesh* mesh;
            std::vector<Math::Matrix4> transform_instances;
            i32 count;
        };
        
    public:
        Renderer();
        ~Renderer();

        void begin();
        void submit();

        void add_to_queue(Graphics::Mesh* mesh, Core::Transform& transform);

        void draw_rect(Math::Vector2 position, u32 width, u32 height, f32 rotation);
    private:
        VAO vao;
        VBO transform_instances_;
        Shader default_shader_;
        Mesh quad_;

        void setup_default_meshes();

        std::vector<RenderRequest> render_queue;
    };
}