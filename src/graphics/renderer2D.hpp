#pragma once
#include <memory>
#include <vector>
#include <core/types.hpp>

namespace Lux::Graphics{
    class Renderer2D{
    public:
        Renderer2D();
        ~Renderer2D();

        void begin();
        void submit();

        void render_quad(f32 x, f32 y);
    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
        std::vector<f32> instance_queue;

        void add_to_queue(f32 x, f32 y);
    };
}