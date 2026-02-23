#pragma once

#include <platform/native.hpp>

namespace Lux::Platform{
    struct System;
    struct Window;
    
    class GraphicsContext{
    public:
        const ContextNativeData&        native;
        const SurfaceNativeSettings&    surface_settings;

        GraphicsContext(const System& system);
        ~GraphicsContext();

        bool create(const Window& window);
        void make_current();
        void swap_buffers();

        
        private:
        ContextNativeData   native_;
        SurfaceNativeSettings surface_settings_;
        const System&       system_;
        const Window*       window_ = nullptr;
        
        static void* get_fn_address(const char* fn_name);
    };
}