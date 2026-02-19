#include "platform/graphics_context.h"
#include "platform/system.h"
#include <core/application.h>
#include <core/time.h>
#include <memory>
#include <platform/window.h>

struct Lux::Application::AppImpl{
    Lux::Platform::System           m_system;
    Lux::Platform::GraphicsContext  m_context;
    Lux::Platform::Window           m_window;

    AppImpl(i32 width, i32 height, const char* title)
        : m_system(),
        m_context(m_system),
        m_window(m_system, m_context.query_requirements(), width, height, title)
    {}
};

Lux::Application::Application(i32 width, i32 height, const char* title)
    :delta_time(),
     app_impl(std::make_unique<AppImpl>(width, height, title))
{
    app_impl->m_context.create(app_impl->m_window);
    app_impl->m_context.make_current();
    app_impl->m_window.m_callback = Lux::Input::on_event;
    app_impl->m_window.show();
}

Lux::Application::~Application() = default;

void Lux::Application::run(){
    loop();
}

void Lux::Application::loop(){
    Time last_time;
    Time current_time;

    last_time = Time::now();
    
    while(!app_impl->m_window.should_close()){
        current_time = Time::now();
        delta_time = current_time - last_time;
        last_time = current_time;

        app_impl->m_window.poll_events();
        update();
        render();
        app_impl->m_context.swap_buffers();
        Input::flush_frame_data();
    }
}