#include <platform/detect.hpp>
#ifdef PLATFORM_WINDOWS

#include <platform/window.hpp>
#include <platform/system.hpp>
#include <core/debug.hpp>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <windowsx.h>

static bool class_registered = false;

Lux::Core::Keyboard::Key translate_key(WPARAM key, LPARAM lparam){
    if(key >= 'A' && key <= 'Z'){
        return (Lux::Core::Keyboard::Key)(key - 'A' + 1);
    }

    if(key >= '0' && key <= '9'){
        return (Lux::Core::Keyboard::Key)(key - '0' + (int)Lux::Core::Keyboard::Key::Z + 1);
    }

    switch(key){
        case VK_ESCAPE:
            return Lux::Core::Keyboard::Key::Escape;
        case VK_SPACE:
            return Lux::Core::Keyboard::Key::Space;
        case VK_RETURN:
            return Lux::Core::Keyboard::Key::Enter;
        case VK_BACK:
            return Lux::Core::Keyboard::Key::Backspace;
        
        case VK_UP:
            return Lux::Core::Keyboard::Key::Up;
        case VK_DOWN:
            return Lux::Core::Keyboard::Key::Down;
        case VK_LEFT:
            return Lux::Core::Keyboard::Key::Left;
        case VK_RIGHT:
            return Lux::Core::Keyboard::Key::Right;
        
        case VK_F1:
            return Lux::Core::Keyboard::Key::F1;
        case VK_F2:
            return Lux::Core::Keyboard::Key::F2;
        case VK_F3:
            return Lux::Core::Keyboard::Key::F3;
        case VK_F4:
            return Lux::Core::Keyboard::Key::F4;
        case VK_F5:
            return Lux::Core::Keyboard::Key::F5;
        case VK_F6:
            return Lux::Core::Keyboard::Key::F6;
        case VK_F7:
            return Lux::Core::Keyboard::Key::F7;
        case VK_F8:
            return Lux::Core::Keyboard::Key::F8;
        case VK_F9:
            return Lux::Core::Keyboard::Key::F9;
        case VK_F10:
            return Lux::Core::Keyboard::Key::F10;
        case VK_F11:
            return Lux::Core::Keyboard::Key::F11;
        case VK_F12:
            return Lux::Core::Keyboard::Key::F12;

        case VK_DELETE:
            return Lux::Core::Keyboard::Key::Delete;
        case VK_PRIOR:
            return Lux::Core::Keyboard::Key::PageUp;
        case VK_NEXT:
            return Lux::Core::Keyboard::Key::PageDown;
        case VK_HOME:
            return Lux::Core::Keyboard::Key::Home;
        case VK_END:
            return Lux::Core::Keyboard::Key::End;
        case VK_INSERT:
            return Lux::Core::Keyboard::Key::Insert;
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
            return shift == VK_LSHIFT ? Lux::Core::Keyboard::Key::LShift : Lux::Core::Keyboard::Key::RShift;
        }
        
        //The extended bit indicates if the key is the Left one
        case VK_CONTROL:
            return is_extended ? Lux::Core::Keyboard::Key::RCtrl : Lux::Core::Keyboard::Key::LCtrl;
        case VK_MENU:
            return is_extended ? Lux::Core::Keyboard::Key::RAlt : Lux::Core::Keyboard::Key::LAlt;
    }

    return Lux::Core::Keyboard::Key::Unknown;
}



LRESULT CALLBACK window_callback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
    Lux::Platform::Window* window = (Lux::Platform::Window*) GetWindowLongPtrA(hwnd, GWLP_USERDATA);

    if(window){
        Lux::Core::Event event{};
        bool dispatch = false;

        switch(msg){
            case WM_CLOSE:
                window->close();
                break;

            //keyboard
            case WM_SYSKEYDOWN:
            case WM_KEYDOWN:
                event.type = Lux::Core::Event::Type::Keyboard;
                event.keyboard.state = Lux::Core::Keyboard::State::Pressed;
                event.keyboard.key = translate_key(wparam, lparam);
                dispatch = true;
                break;

            case WM_SYSKEYUP:
            case WM_KEYUP:
                event.type = Lux::Core::Event::Type::Keyboard;
                event.keyboard.state = Lux::Core::Keyboard::State::Released;
                event.keyboard.key = translate_key(wparam, lparam);
                dispatch = true;
                break;

            //mouse
            case WM_MOUSEMOVE:
                event.type = Lux::Core::Event::Type::Mouse;
                event.mouse.state = Lux::Core::Mouse::State::Moved;
                event.mouse.x = (i32) GET_X_LPARAM(lparam);
                event.mouse.y = (i32) GET_Y_LPARAM(lparam);
                dispatch = true;
                break;

            case WM_LBUTTONDOWN:
                event.type = Lux::Core::Event::Type::Mouse;
                event.mouse.state = Lux::Core::Mouse::State::Pressed;
                event.mouse.button = Lux::Core::Mouse::Button::Left;
                dispatch = true;
                break;

            case WM_RBUTTONDOWN:
                event.type = Lux::Core::Event::Type::Mouse;
                event.mouse.state = Lux::Core::Mouse::State::Pressed;
                event.mouse.button = Lux::Core::Mouse::Button::Right;
                dispatch = true;
                break;

            case WM_LBUTTONUP:
                event.type = Lux::Core::Event::Type::Mouse;
                event.mouse.state = Lux::Core::Mouse::State::Released;
                event.mouse.button = Lux::Core::Mouse::Button::Left;
                dispatch = true;
                break;

            case WM_RBUTTONUP:
                event.type = Lux::Core::Event::Type::Mouse;
                event.mouse.state = Lux::Core::Mouse::State::Released;
                event.mouse.button = Lux::Core::Mouse::Button::Right;
                dispatch = true;
                break;

            case WM_MOUSEWHEEL:
                event.type = Lux::Core::Event::Type::Mouse;
                event.mouse.state = Lux::Core::Mouse::State::Scrolled;
                event.mouse.delta_scroll = GET_WHEEL_DELTA_WPARAM(wparam);
                dispatch = true;
                break;
    
            //action
            case WM_SIZE:
                window->width_ = static_cast<i32>(LOWORD(lparam));
                window->height_ = static_cast<i32>(HIWORD(lparam));
                switch(wparam){
                    case SIZE_MINIMIZED:
                        event.type = Lux::Core::Event::Type::Action;
                        event.action = Lux::Core::Action::Minimize;
                        dispatch = true;
                        break;

                    case SIZE_MAXIMIZED:
                        event.type = Lux::Core::Event::Type::Action;
                        event.action = Lux::Core::Action::Resize;
                        dispatch = true;
                        break;

                    case SIZE_RESTORED:
                        event.type = Lux::Core::Event::Type::Action;
                        event.action = Lux::Core::Action::Resize;
                        dispatch = true;
                        break;
                }
        }

        if(dispatch && window->callback_){
            window->callback_(event);
        }
    }

    return DefWindowProcA(hwnd, msg, wparam, lparam);
}

Lux::Platform::Window::Window(const System& system, const SurfaceNativeSettings& surface_settings, i32 width, i32 height, const char* title)
    : system_(system)
    , native(native_)
    , width_(width)
    , height_(height)

{
    if(!class_registered){
        WNDCLASSA wc = {};

        wc.lpszClassName    = "window_class";
        wc.hInstance        = (HINSTANCE) system.native.hinstance;
        wc.hCursor          = LoadCursor(nullptr, IDC_ARROW);
        wc.hIcon            = LoadIcon(nullptr, IDI_APPLICATION);
        wc.lpfnWndProc      = window_callback;
        wc.style            = CS_OWNDC;

        LUX_VERIFY(RegisterClassA(&wc),"failed to register window class");

        class_registered = true;
    }

    RECT rect = {0,0,width,height};

    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);

    width = rect.right - rect.left;
    height = rect.bottom - rect.top;

    int x = GetSystemMetrics(SM_CXSCREEN)/2 - width/2;
    int y = GetSystemMetrics(SM_CYSCREEN)/2 - height/2;

    native_.hwnd = CreateWindowExA(0, "window_class", title, WS_OVERLAPPEDWINDOW, x, y, width, height, nullptr, nullptr, (HINSTANCE) system.native.hinstance, nullptr);

    LUX_VERIFY(native.hwnd, "failed to create a window");

    HDC hdc = GetDC((HWND) native.hwnd);

    PIXELFORMATDESCRIPTOR pfd;
    DescribePixelFormat(hdc, surface_settings.pixel_format, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

    SetPixelFormat(hdc, surface_settings.pixel_format, &pfd);

    SetWindowLongPtrA((HWND) native.hwnd, GWLP_USERDATA, (LONG_PTR)this);

    ReleaseDC((HWND) native.hwnd, hdc);
}

Lux::Platform::Window::~Window(){
    if(native.hwnd){
        DestroyWindow((HWND) native.hwnd);
    }
}

bool Lux::Platform::Window::show(){
    if(native.hwnd){
        ShowWindow((HWND) native.hwnd, SW_SHOW);
        return true;
    }

    return false;
}

bool Lux::Platform::Window::close(){
    if(!close_flag_){
        close_flag_ = true;
        return true;
    }

    return false;
}

void Lux::Platform::Window::poll_events(){
    MSG msg;
    while(PeekMessageA(&msg, (HWND) native.hwnd, 0, 0, PM_REMOVE)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

bool Lux::Platform::Window::should_close(){
    return close_flag_;
}

#endif