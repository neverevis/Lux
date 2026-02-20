#pragma once

#include <core/event.hpp>
#include <platform/native.hpp>
#include <platform/system.hpp>

namespace Lux::Platform{
    class Window{
    public:
        const WindowNativeData& native;
        const u16& width;
        const u16& height;

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

        u16 width_;
        u16 height_;
    };
}