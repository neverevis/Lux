#pragma once

#include <memory>
#include <core/event.h>

namespace Lux{
    class Window{
    public:
        Window(int width, int height, const char* title);
        ~Window();

        bool    show();
        bool    close();
        void    poll_events();
        bool    should_close();
        void*   get_native_handle();
        void    set_callback(void (*callback_ptr)(Event& event));
        void    dispatch_event(Event& event);
    
    private:
        void*   m_native_handle                     = nullptr;
        bool    m_close_flag                        = false;
        void    (*m_event_callback)(Event& event)   = nullptr;

    };
}