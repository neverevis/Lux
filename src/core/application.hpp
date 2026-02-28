#pragma once
#include <core/types.hpp>
#include <core/time.hpp>
#include <math/vector2.hpp>
#include <memory>

namespace Lux::Core{
    class Application{
        public:
        Lux::Core::Time delta_time;
        
        Application(i32 width, i32 height, const char* title);
        ~Application();
        
        void    run();
        
        virtual void setup() = 0;
        virtual void update() = 0;
        virtual void render() = 0;

        void draw_rect(const Math::Vector2& position, u32 width, u32 height, f32 rotation, const Math::Vector2& pivot);
        u8 get_current_buffer();
    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
        
        void loop();
    };
}