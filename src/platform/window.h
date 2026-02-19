#pragma once

#include "platform/linux/egl_handles.h"
#include <core/event.h>
#include <platform/handles.h>
#include <platform/system.h>

namespace Lux::Platform{
    class Window{
    public:
        void (*m_callback)(Event& event) = nullptr;

        Window(const System& system, const GraphicsRequirements&, i32 width, i32 height, const char* title);
        ~Window();

        bool    show();
        bool    close();
        void    poll_events();
        bool    should_close();

        u16     width();
        u16     height();

        const WindowHandle& get_native_handle() const;
    
    private:
        WindowHandle    m_window_handle;
        const System&   m_system;

        bool m_close_flag = false;

        u16 m_width;
        u16 m_height;

    };
}