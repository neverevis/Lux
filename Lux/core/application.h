#pragma once
#include <core/types.h>
#include <core/time.h>
#include <platform/window.h>
#include <platform/gl_context.h>

namespace Lux{
    class Application{
    public:
        Lux::Time delta_time;

        Application(i32 width, i32 height, const char* title);
        
        void    run();

        virtual void update() = 0;
        virtual void render() = 0;
        virtual ~Application() = default;
    private:
        void loop();

        Lux::Window     m_window;
        Lux::GLContext  m_gl;
    };
}