#pragma once
#include <platform/system.hpp>
#include <platform/window.hpp>
#include <platform/handles.hpp>

namespace Lux::Platform{
    class GraphicsContext{
    public:
        GraphicsContext(const System& system);
        ~GraphicsContext();

        bool create(const Window& window);
        void make_current();
        void swap_buffers();
        const GraphicsRequirements query_requirements();
    private:
        ContextHandle m_context_handle;
        const System& m_system;
        const Window* m_window = nullptr;
    };
}