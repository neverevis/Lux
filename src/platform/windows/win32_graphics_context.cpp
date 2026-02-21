#include <platform/detect.hpp>
#ifdef PLATFORM_WINDOWS

#include <platform/window.hpp>
#include <platform/graphics_context.hpp>

#include <graphics/gl.hpp>

#include <core/debug.hpp>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <glcorearb.h>
#include <wglext.h>

Lux::Platform::GraphicsContext::GraphicsContext(const Lux::Platform::System& system)
    : system_(system)
    , native(native_)
    , surface_settings(surface_settings_)
{

    WNDCLASSA wc = {};
    wc.hInstance = (HINSTANCE) system.native.hinstance;
    wc.lpszClassName = "dummy_class";
    wc.lpfnWndProc = DefWindowProc;

    RegisterClass(&wc);

    HWND dummy_hwnd = CreateWindowExA(0, "dummy_class", "", WS_OVERLAPPEDWINDOW, 0, 0, 1, 1, nullptr, nullptr, (HINSTANCE) system.native.hinstance, nullptr);
    HDC dummy_hdc = GetDC(dummy_hwnd);

    PIXELFORMATDESCRIPTOR pfd =  {};
    pfd.nSize           = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.iPixelType      = PFD_TYPE_RGBA;
    pfd.iLayerType      = PFD_MAIN_PLANE;
    pfd.dwFlags         = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;
    pfd.nVersion        = 1;
    pfd.cColorBits      = 32;
    pfd.cDepthBits      = 24;
    pfd.cStencilBits    = 8;

    int pixel_format = ChoosePixelFormat(dummy_hdc, &pfd);

    SetPixelFormat(dummy_hdc, pixel_format, &pfd);

    HGLRC dummy_hglrc = wglCreateContext(dummy_hdc);

    wglMakeCurrent(dummy_hdc, dummy_hglrc);

    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC) wglGetProcAddress("wglChoosePixelFormatARB");

    int pixel_attribs[] = {
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
    WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
    WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 24,
    WGL_STENCIL_BITS_ARB, 8,
    0
    
    };

    UINT num_formats;

    wglChoosePixelFormatARB(dummy_hdc, pixel_attribs, nullptr, 1, &surface_settings_.pixel_format, &num_formats);

    native_.wglCreateContextAttribsARB = (void*) wglGetProcAddress("wglCreateContextAttribsARB");

    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(dummy_hglrc);
    ReleaseDC(dummy_hwnd ,dummy_hdc);
    DestroyWindow(dummy_hwnd);
}

Lux::Platform::GraphicsContext::~GraphicsContext(){
  
}

bool Lux::Platform::GraphicsContext::create(const Window& window){
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) native.wglCreateContextAttribsARB;

    native_.hdc = GetDC((HWND) window.native.hwnd);

    int version[8][2] = {{4,6},{4,5},{4,4},{4,3},{4,2},{4,1},{4,0},{3,3}};
    int i = 0;

    bool done = false;
    bool success = false;

    while(!done){
        int attribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, version[i][0],
            WGL_CONTEXT_MINOR_VERSION_ARB, version[i][1],
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };

        native_.hglrc = wglCreateContextAttribsARB((HDC) native.hdc, nullptr, attribs);

        if(native_.hglrc){
            LUX_INFO("OpenGL Core {}.{}",version[i][0],version[i][1]);
            done = true;
            success = true;
        }else if(i < 7){
            i++;
        }else{
            LUX_INFO("Failed to load GL Context");
            done = true;
        }
    }

    if(!success){
        return false;
    }

    Lux::Graphics::gl::init();

    return success;
}

void Lux::Platform::GraphicsContext::make_current(){
    
    wglMakeCurrent((HDC) native.hdc, (HGLRC) native.hglrc);
}

void Lux::Platform::GraphicsContext::swap_buffers(){
    SwapBuffers((HDC) native.hdc);
}

#endif