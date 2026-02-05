#pragma once

#include <memory>

namespace Lux{
    class Window{
    public:
        struct Data;
        std::unique_ptr<Data>   m_data;
        
        Window(int width, int height, const char* title);
        ~Window();

        bool show();
        bool close();
        void poll_events();
        bool should_close();
        void swap_buffers();
        
    };
}