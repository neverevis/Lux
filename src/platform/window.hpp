#pragma once

#include <core/event.hpp>
#include <platform/native.hpp>

namespace Lux::Platform{
    class System;
    class Window{
    public:
        const WindowNativeData& native;
        u16 width_;
        u16 height_;

        void (*callback_)(Event& event) = nullptr;

        Window(const System& system, const SurfaceNativeSettings& surface_settings, i32 width, i32 height, const char* title);
        ~Window();

        bool    show();
        bool    close();
        void    poll_events();
        bool    should_close();
    
    private:
        WindowNativeData    native_;
        const System&       system_;

        bool close_flag_ = false;
    };
}