#pragma once

#include <memory>

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
    
    private:
        void*   m_native_handle = nullptr;
        bool    m_close_flag = false;
    };
}