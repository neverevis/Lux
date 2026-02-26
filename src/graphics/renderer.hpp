#pragma once

#include <core/memory.hpp>
#include <graphics/resource_manager.hpp>
#include <math/matrix4.hpp>
#include <core/types.hpp>
#include <graphics/mesh.hpp>
#include <graphics/shader.hpp>
#include <graphics/vao.hpp>
#include <core/transform.hpp>
#include <math/vector2.hpp>

namespace Lux::Graphics{
    class Renderer{
        struct RenderCommand{
            u32     mesh_id;
            u32     instance_count;
            
            void*   arena_bucket;
            size_t  arena_offset;
        };
        
    public:
        Renderer();
        ~Renderer();

        void begin();
        void submit();

        void add_to_queue(u32 mesh_id, Core::Transform& transform);

        void draw_rect(Math::Vector2 position, u32 width, u32 height, f32 rotation);
    private:
        ResourceManager resource_manager;
        Shader          default_shader_;
        Mesh            quad_;

        VAO             vao;
        VBO             transform_vbo_;

        Core::Arena     transform_arena_;
        Math::Matrix4*  transform_instances_;

        void setup_default_meshes();
    };
}