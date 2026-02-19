#pragma once
#include <platform/window.h>

namespace Lux::Platform{
    class GraphicsContext{
    public:
        GraphicsContext(const System& system);
        ~GraphicsContext();

        bool create(const Window& window);
        void make_current();
        void swap_buffers();
    private:
        ContextHandle m_context_handle;
        const System& m_system;
        const Window* m_window = nullptr;
    };
}