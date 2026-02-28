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
        struct RenderObject{
            u32             instance_count;
            u32             base_instance_index;

            Math::Matrix4*  transform_arena_bucket_ptr;
            size_t          transform_arena_bucket_offset;
        };
        
    public:
        Renderer(Platform::Window& window);
        ~Renderer();

        void begin();
        void end();

        void submit(u32 mesh_id, Core::Transform& transform);

        u32 load_mesh(VertexData* vertices, IndexData* indices, u32 vertices_count, u32 indices_count, u32 max_instances);
        void unload_mesh(u32 mesh_id);

        void draw_rect(Math::Vector2 position, u32 width, u32 height, f32 rotation, const Math::Vector2& pivot);

    private:
        Platform::Window&                   window_;
        ResourceManager                     resource_manager;
        Memory::StaticPool<RenderObject>    render_table;
        std::vector<u32>                    active_ids;

        VAO                                 vao;
        VBO                                 transform_vbo_;

        Shader                              default_shader_;
        u32                                 quad_;

        Memory::Arena                       transform_arena_;
        Math::Matrix4*                      transform_instances_ptr_;

        void setup_default_meshes();
    };
}