#pragma once

#include <core/types.hpp>
#include <graphics/mesh.hpp>
#include <graphics/shader.hpp>
#include <graphics/vao.hpp>
#include <vector>

namespace Lux::Graphics{
    class Renderer{
        struct RenderRequest{
            Mesh* mesh;
            i32 count;
        };
        
    public:
        Renderer();
        ~Renderer();

        void begin();
        void submit();

        void add_to_queue(Mesh* mesh);
        void draw_rect();
    private:
        VAO vao;
        Shader default_shader_;
        Mesh quad_;

        std::vector<RenderRequest> render_queue;
    };
}