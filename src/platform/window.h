#pragma once

#include <memory>
#include <core/event.h>

namespace Lux{
    class Window{
    public:
        void (*m_callback)(Event& event) = nullptr;

        Window(int width, int height, const char* title);
        ~Window();

        bool    show();
        bool    close();
        void    poll_events();
        bool    should_close();
        void*   get_native_handle();
    
    private:
        void*   m_native_handle = nullptr;
        bool    m_close_flag    = false;

    };
}