#pragma once

namespace Lux::Platform{
    struct ContextNativeData{
        void* egl_display = nullptr;
        void* egl_config  = nullptr;
        void* egl_context = nullptr;
        void* egl_surface = nullptr;
    };

    struct SurfaceNativeSettings{
        unsigned long visual_id = 0;
    };
}