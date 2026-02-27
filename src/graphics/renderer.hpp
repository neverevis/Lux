#pragma once

#include <memory/arena.hpp>
#include <graphics/resource_manager.hpp>
#include <math/matrix4.hpp>
#include <core/types.hpp>
#include <graphics/mesh.hpp>
#include <graphics/shader.hpp>
#include <graphics/vao.hpp>
#include <core/transform.hpp>
#include <math/vector2.hpp>
#include <platform/window.hpp>

namespace Lux::Graphics{
    class Renderer{
        struct RenderCommand{
            u32     mesh_id;
            u32     instance_count;
            
            void*   arena_bucket;
            size_t  arena_offset;
        };
        
    public:
        Renderer(Platform::Window& window);
        ~Renderer();

        void begin();
        void end();

        void submit(u32 mesh_id, Core::Transform& transform);

        void draw_rect(Math::Vector2 position, u32 width, u32 height, f32 rotation);

    private:
        ResourceManager             resource_manager;
        std::vector<RenderCommand>  render_queue;

        VAO                         vao;
        VBO                         transform_vbo_;

        Shader                      default_shader_;
        u32                         quad_;

        Memory::Arena               transform_arena_;
        Math::Matrix4*              transform_instances_;

        void setup_default_meshes();
    };
}