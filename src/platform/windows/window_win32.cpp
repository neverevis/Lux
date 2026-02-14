#include <platform/platform.h>
#ifdef PLATFORM_WINDOWS

#include <platform/window.h>
#include <core/debug.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <windowsx.h>

static bool class_registered = false;

Lux::Keyboard::Key translate_key(WPARAM key, LPARAM lparam){
    if(key >= 'A' && key <= 'Z'){
        return (Lux::Keyboard::Key)(key - 'A' + 1);
    }

    if(key >= '0' && key <= '9'){
        return (Lux::Keyboard::Key)(key - '0' + (int)Lux::Keyboard::Key::Z + 1);
    }

    switch(key){
        case VK_ESCAPE:
            return Lux::Keyboard::Key::Escape;
        case VK_SPACE:
            return Lux::Keyboard::Key::Space;
        case VK_RETURN:
            return Lux::Keyboard::Key::Enter;
        case VK_BACK:
            return Lux::Keyboard::Key::Backspace;
        
        case VK_UP:
            return Lux::Keyboard::Key::Up;
        case VK_DOWN:
            return Lux::Keyboard::Key::Down;
        case VK_LEFT:
            return Lux::Keyboard::Key::Left;
        case VK_RIGHT:
            return Lux::Keyboard::Key::Right;
        
        case VK_F1:
            return Lux::Keyboard::Key::F1;
        case VK_F2:
            return Lux::Keyboard::Key::F2;
        case VK_F3:
            return Lux::Keyboard::Key::F3;
        case VK_F4:
            return Lux::Keyboard::Key::F4;
        case VK_F5:
            return Lux::Keyboard::Key::F5;
        case VK_F6:
            return Lux::Keyboard::Key::F6;
        case VK_F7:
            return Lux::Keyboard::Key::F7;
        case VK_F8:
            return Lux::Keyboard::Key::F8;
        case VK_F9:
            return Lux::Keyboard::Key::F9;
        case VK_F10:
            return Lux::Keyboard::Key::F10;
        case VK_F11:
            return Lux::Keyboard::Key::F11;
        case VK_F12:
            return Lux::Keyboard::Key::F12;

        case VK_DELETE:
            return Lux::Keyboard::Key::Delete;
        case VK_PRIOR:
            return Lux::Keyboard::Key::PageUp;
        case VK_NEXT:
            return Lux::Keyboard::Key::PageDown;
        case VK_HOME:
            return Lux::Keyboard::Key::Home;
        case VK_END:
            return Lux::Keyboard::Key::End;
        case VK_INSERT:
            return Lux::Keyboard::Key::Insert;
    }

    /*
        =-=- Generic WParam Keys -=-=
        The following keys are not specified (left or right) by WParam.
        It must have the scancode or the extended bit on the LParam to get the Virtual Key
    */

    /* The scancode is localized in the 16 to 24 bit within the LParam. 
    to extract that, it must shift 16 bits to right and apply a mask that preserves only the 8 last bits, */
    u32 scancode = (lparam >> 16) & 0xFF;

    /* the 24 bit indicates if the key is right in most cases. */
    bool is_extended = (lparam >> 24) & 0x1;

    switch(key){
        //Shift message doesn't support extended bit so it need to be translated by windows using the scancode
        case VK_SHIFT:{
            WPARAM shift = MapVirtualKeyA(scancode, MAPVK_VSC_TO_VK_EX);
            return shift == VK_LSHIFT ? Lux::Keyboard::Key::LShift : Lux::Keyboard::Key::RShift;
        }
        
        //The extended bit indicates if the key is the Left one
        case VK_CONTROL:
            return is_extended ? Lux::Keyboard::Key::RCtrl : Lux::Keyboard::Key::LCtrl;
        case VK_MENU:
            return is_extended ? Lux::Keyboard::Key::RAlt : Lux::Keyboard::Key::LAlt;
    }

    return Lux::Keyboard::Key::Unknown;
}



LRESULT CALLBACK window_callback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
    Lux::Window* window = (Lux::Window*) GetWindowLongPtrA(hwnd, GWLP_USERDATA);

    if(window && window->m_callback){
        Lux::Event event{};
        bool dispatch = false;

        switch(msg){
            case WM_CLOSE:
                window->close();
                break;

            //keyboard
            case WM_SYSKEYDOWN:
            case WM_KEYDOWN:
                event.type = Lux::Event::Type::Keyboard;
                event.keyboard.state = Lux::Keyboard::State::Pressed;
                event.keyboard.key = translate_key(wparam, lparam);
                dispatch = true;
                break;

            case WM_SYSKEYUP:
            case WM_KEYUP:
                event.type = Lux::Event::Type::Keyboard;
                event.keyboard.state = Lux::Keyboard::State::Released;
                event.keyboard.key = translate_key(wparam, lparam);
                dispatch = true;
                break;

            //mouse
            case WM_MOUSEMOVE:
                event.type = Lux::Event::Type::Mouse;
                event.mouse.state = Lux::Mouse::State::Moved;
                event.mouse.x = (i32) GET_X_LPARAM(lparam);
                event.mouse.y = (i32) GET_Y_LPARAM(lparam);
                dispatch = true;
                break;

            case WM_LBUTTONDOWN:
                event.type = Lux::Event::Type::Mouse;
                event.mouse.state = Lux::Mouse::State::Pressed;
                event.mouse.button = Lux::Mouse::Button::Left;
                dispatch = true;
                break;

            case WM_RBUTTONDOWN:
                event.type = Lux::Event::Type::Mouse;
                event.mouse.state = Lux::Mouse::State::Pressed;
                event.mouse.button = Lux::Mouse::Button::Right;
                dispatch = true;
                break;

            case WM_LBUTTONUP:
                event.type = Lux::Event::Type::Mouse;
                event.mouse.state = Lux::Mouse::State::Released;
                event.mouse.button = Lux::Mouse::Button::Left;
                dispatch = true;
                break;

            case WM_RBUTTONUP:
                event.type = Lux::Event::Type::Mouse;
                event.mouse.state = Lux::Mouse::State::Released;
                event.mouse.button = Lux::Mouse::Button::Right;
                dispatch = true;
                break;

            case WM_MOUSEWHEEL:
                event.type = Lux::Event::Type::Mouse;
                event.mouse.state = Lux::Mouse::State::Scrolled;
                event.mouse.delta_scroll = GET_WHEEL_DELTA_WPARAM(wparam);
                dispatch = true;
                break;
    
            //action
            case WM_SIZE:
                switch(wparam){
                    case SIZE_MINIMIZED:
                        event.type = Lux::Event::Type::Action;
                        event.action = Lux::Action::Minimize;
                        dispatch = true;
                        break;

                    case SIZE_MAXIMIZED:
                        event.type = Lux::Event::Type::Action;
                        event.action = Lux::Action::Resize;
                        dispatch = true;
                        break;

                    case SIZE_RESTORED:
                        event.type = Lux::Event::Type::Action;
                        event.action = Lux::Action::Resize;
                        dispatch = true;
                        break;
                }
        }

        if(dispatch){
            window->m_callback(event);
        }
    }

    return DefWindowProcA(hwnd, msg, wparam, lparam);
}

Lux::Window::Window(int width, int height, const char* title){
    HINSTANCE instance = GetModuleHandleA(nullptr);

    LUX_VERIFY(instance, "failed to get instance");

    if(!class_registered){
        WNDCLASSA wc = {};

        wc.lpszClassName = "window_class";
        wc.hInstance = instance;
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
        wc.lpfnWndProc = window_callback;
        wc.style = CS_OWNDC;

        LUX_VERIFY(RegisterClassA(&wc),"failed to register window class");

        class_registered = true;
    }

    RECT rect = {0,0,width,height};

    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);

    width = rect.right - rect.left;
    height = rect.bottom - rect.top;

    int x = GetSystemMetrics(SM_CXSCREEN)/2 - width/2;
    int y = GetSystemMetrics(SM_CYSCREEN)/2 - height/2;

    m_native_handle = CreateWindowExA(0, "window_class", title, WS_OVERLAPPEDWINDOW, x, y, width, height, nullptr, nullptr, instance, nullptr);

    LUX_VERIFY(m_native_handle, "failed to create a window");

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

u16 Lux::Window::width(){
    RECT r;
    GetClientRect((HWND) m_native_handle, &r);

    return r.right - r.left;
}

u16 Lux::Window::height(){
    RECT r;
    GetClientRect((HWND) m_native_handle, &r);

    return r.bottom - r.top;
}

#endif