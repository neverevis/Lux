#include <platform/platform.h>
#ifdef PLATFORM_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <glcorearb.h>
#include <wglext.h>
#include <platform/gl_context.h>
#include <iostream>

Lux::GLContext::GLContext(Lux::Window& window){
    PFNWGLCHOOSEPIXELFORMATARBPROC      wglChoosePixelFormatARB;
    PFNWGLCREATECONTEXTATTRIBSARBPROC   wglCreateContextAttribsARB;

    {
        Lux::Window dummy(1,1,"");

        HWND dummy_hwnd = (HWND) dummy.get_native_handle();
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

        wglChoosePixelFormatARB     = (PFNWGLCHOOSEPIXELFORMATARBPROC)      wglGetProcAddress("wglChoosePixelFormatARB");
        wglCreateContextAttribsARB  = (PFNWGLCREATECONTEXTATTRIBSARBPROC)   wglGetProcAddress("wglCreateContextAttribsARB");

        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(dummy_hglrc);
        ReleaseDC(dummy_hwnd ,dummy_hdc);
    }

    m_window    = (void*) window.get_native_handle();
    m_display   = (void*) GetDC((HWND) m_window);

    int pixel_attribs[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        0
    };

    int pixel_format;
    UINT num_formats;

    wglChoosePixelFormatARB((HDC) m_display, pixel_attribs, nullptr, 1, &pixel_format, &num_formats);

    PIXELFORMATDESCRIPTOR pfd;
    DescribePixelFormat((HDC) m_display, pixel_format, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

    SetPixelFormat((HDC) m_display, pixel_format, &pfd);

    int attribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 6,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    m_context = wglCreateContextAttribsARB((HDC) m_display, 0, attribs);
}

Lux::GLContext::~GLContext(){
    if(wglGetCurrentContext() == (HGLRC) m_context){
        wglMakeCurrent(nullptr, nullptr);
    }
    wglDeleteContext((HGLRC) m_context);
    ReleaseDC((HWND) m_window, (HDC) m_display);
}

void Lux::GLContext::make_current(){
    wglMakeCurrent((HDC)m_display, (HGLRC)m_context);
}

void Lux::GLContext::swap_buffers(){
    SwapBuffers((HDC) m_display);
}

#endif