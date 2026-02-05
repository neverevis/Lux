#pragma once
#include <core/types.h>
#include <platform/window.h>
#include <platform/gl_context.h>

namespace Lux{
    class Application{
    public:
        Application(i32 width, i32 height, const char* title);
        
        void run();
        
        virtual void update(f64 delta_time) = 0;
        virtual void render() = 0;
        virtual ~Application() = default;
    private:
        void loop();

        Lux::Window window;
        Lux::GLContext gl;
        f64 delta_time;
    };
}