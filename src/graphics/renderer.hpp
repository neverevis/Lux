#pragma once

#include <graphics/resource_manager.hpp>
#include <graphics/shader.hpp>
#include <graphics/mesh.hpp>
#include <graphics/vao.hpp>

#include <memory/arena.hpp>

#include <math/matrix4.hpp>
#include <math/vector2.hpp>

#include <core/types.hpp>
#include <core/transform.hpp>

#include <platform/window.hpp>

namespace Lux::Graphics{
    class Renderer{
        struct RenderObject{
            u32             instance_count;
            u32             base_instance_index;
            u32             max_instances;

            Math::Matrix4*  transform_arena_bucket_ptr;
            size_t          transform_arena_bucket_offset;
        };
        
    public:
        Renderer(Platform::Window& window, u8 num_buffers);
        ~Renderer();

        void begin();
        void end();

        void submit(u32 mesh_id, Core::Transform& transform);

        u32 load_mesh(VertexData* vertices, IndexData* indices, u32 vertices_count, u32 indices_count, u32 max_instances);
        void unload_mesh(u32 mesh_id);

        void draw_rect(const Math::Vector2& position, u32 width, u32 height, f32 rotation, const Math::Vector2& pivot);
        void draw_circle(const Math::Vector2& position, u32 width, u32 height, f32 rotation, const Math::Vector2& pivot);

        void resize(u32 width, u32 height);

        void set_camera_position(Math::Vector3& position);

    private:
        Platform::Window&                   window_;
        ResourceManager                     resource_manager;
        Memory::StaticPool<RenderObject>    render_table;
        std::vector<u32>                    active_ids;

        VAO                                 vao;
        VBO                                 transform_vbo_;

        Shader                              default_shader_;
        u32                                 quad_;
        u32                                 circle_;

        Memory::Arena                       transform_arena_;
        Math::Matrix4*                      transform_instances_ptr_;

        u8                                  num_buffers_;
        u8                                  current_buffer_;

        i64                                 instances_usage;

        Math::Matrix4                       view;
        Math::Vector3                       camera_position;

        void setup_default_meshes();
    };
}