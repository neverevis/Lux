#include <platform/platform.h>
#ifdef PLATFORM_WINDOWS

#include <platform/window.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

static bool class_registered = false;

Lux::Key translate_key(WPARAM key){
    if(key >= 'A' && key <= 'Z'){
        return (Lux::Key)(key - 'A' + 1);
    }

    if(key >= '0' && key <= '9'){
        return (Lux::Key)((int)Lux::Key::Num0 - '0');
    }

    //TODO -> add keys like escape, enter..

    return Lux::Key::Unknown;
}

LRESULT CALLBACK window_callback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
    Lux::Window* window = (Lux::Window*) GetWindowLongPtrA(hwnd, GWLP_USERDATA);

    if(window){
        Lux::Event event{};
        bool dispatch = false;

        switch(msg){
            case WM_CLOSE:
                window->close();
                break;

            //event types
            case WM_KEYDOWN:
                event.event_type = Lux::EventType::KeyPressed;
                event.key = translate_key(wparam);
                dispatch = true;
                break;

            case WM_KEYUP:
                event.event_type = Lux::EventType::KeyReleased;
                event.key = translate_key(wparam);
                dispatch = true;
                break;

            case WM_MOUSEMOVE:
                event.event_type = Lux::EventType::MouseMoved;
                event.mouse.x = (int) wparam;
                event.mouse.y = (int) lparam;
                dispatch = true;
                break;

            case WM_LBUTTONDOWN:
                event.event_type = Lux::EventType::MousePressed;
                event.mouse_button = Lux::Mouse::Button::Left;
                dispatch = true;
                break;

            case WM_RBUTTONDOWN:
                event.event_type = Lux::EventType::MousePressed;
                event.mouse_button = Lux::Mouse::Button::Right;
                dispatch = true;
                break;

            case WM_LBUTTONUP:
                event.event_type = Lux::EventType::MouseReleased;
                event.mouse_button = Lux::Mouse::Button::Left;
                dispatch = true;
                break;

            case WM_RBUTTONUP:
                event.event_type = Lux::EventType::MouseReleased;
                event.mouse_button = Lux::Mouse::Button::Right;
                dispatch = true;
                break;
        }

        if(dispatch){
            window->dispatch_event(event);
        }
    }

    return DefWindowProcA(hwnd, msg, wparam, lparam);
}

Lux::Window::Window(int width, int height, const char* title){
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

    m_native_handle = CreateWindowExA(0, "window_class", title, WS_OVERLAPPEDWINDOW, x, y, width, height, nullptr, nullptr, instance, nullptr);

    SetWindowLongPtrA((HWND) m_native_handle, GWLP_USERDATA, (LONG_PTR)this);
}

Lux::Window::~Window(){
    if(m_native_handle){
        DestroyWindow((HWND) m_native_handle);
    }
}

bool Lux::Window::show(){
    if(m_native_handle){
        ShowWindow((HWND) m_native_handle, SW_SHOW);
        return true;
    }

    return false;
}

bool Lux::Window::close(){
    if(!m_close_flag){
        m_close_flag = true;
        return true;
    }

    return false;
}

void Lux::Window::poll_events(){
    MSG msg;
    while(PeekMessageA(&msg, (HWND) m_native_handle, 0, 0, PM_REMOVE)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

bool Lux::Window::should_close(){
    return m_close_flag;
}

void* Lux::Window::get_native_handle(){
    return m_native_handle;
}

void Lux::Window::set_callback(void (*callback_ptr)(Event& event)){
    m_event_callback = callback_ptr;
}

void Lux::Window::dispatch_event(Event& event){
    if(m_event_callback){
        m_event_callback(event);
    }
}

#endif