#include <platform/platform.h>
#ifdef PLATFORM_WINDOWS

#include <platform/window.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

static bool class_registered = false;

LRESULT CALLBACK window_callback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
    Lux::Window* window = (Lux::Window*) GetWindowLongPtrA(hwnd, GWLP_USERDATA);

    if(window){
        switch(msg){
            case WM_CLOSE:
                window->close();
                break;
        }
    }

    return DefWindowProcA(hwnd, msg, wparam, lparam);
}

struct Lux::Window::Data{
    HWND    hwnd        =   nullptr;
    HDC     hdc         =   nullptr;
    bool    close_flag  =   false;
};

Lux::Window::Window(int width, int height, const char* title)
    : m_data(std::make_unique<Lux::Window::Data>())
{
    HINSTANCE instance = GetModuleHandleA(nullptr);

    if(!class_registered){
        WNDCLASSA wc = {};

        wc.lpszClassName = "window_class";
        wc.hInstance = instance;
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
        wc.lpfnWndProc = window_callback;
        wc.style = CS_OWNDC;

        RegisterClassA(&wc);

        class_registered = true;
    }

    RECT rect = {0,0,width,height};

    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);

    width = rect.right - rect.left;
    height = rect.bottom - rect.top;

    int x = GetSystemMetrics(SM_CXSCREEN)/2 - width/2;
    int y = GetSystemMetrics(SM_CYSCREEN)/2 - height/2;

    m_data->hwnd = CreateWindowExA(0, "window_class", title, WS_OVERLAPPEDWINDOW, x, y, width, height, nullptr, nullptr, instance, nullptr);

    SetWindowLongPtrA(m_data->hwnd, GWLP_USERDATA, (LONG_PTR)this);
}

Lux::Window::~Window(){
    if(m_data->hdc){
        ReleaseDC(m_data->hwnd, m_data->hdc);
    }
    if(m_data->hwnd){
        DestroyWindow(m_data->hwnd);
    }
}

bool Lux::Window::show(){
    if(m_data->hwnd){
        ShowWindow(m_data->hwnd, SW_SHOW);
        return true;
    }

    return false;
}

bool Lux::Window::close(){
    if(!m_data->close_flag){
        m_data->close_flag = true;
        return true;
    }

    return false;
}

void Lux::Window::poll_events(){
    MSG msg;
    while(PeekMessageA(&msg, m_data->hwnd, 0, 0, PM_REMOVE)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

bool Lux::Window::should_close(){
    return m_data->close_flag;
}

void Lux::Window::swap_buffers(){
    if(m_data->hdc){
        SwapBuffers(m_data->hdc);
    }
}

#endif