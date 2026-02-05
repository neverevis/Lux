#pragma once
#include <platform/window.h>

namespace Lux{
    class GLContext{
    public:
        GLContext(Window& window);
        ~GLContext();

        void make_current();
        void swap_buffers();
    private:
        void* m_window;
        void* m_display;
        void* m_context;
    };
}