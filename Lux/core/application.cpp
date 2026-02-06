#include <core/application.h>
#include <core/time.h>
#include <print>

Lux::Application::Application(i32 width, i32 height, const char* title)
    : m_window(width, height, title),
      m_gl(m_window),
      delta_time()

{
    m_gl.make_current();
    m_window.show();
}

void Lux::Application::run(){
    loop();
}

void Lux::Application::loop(){
    Time last_time;
    Time current_time;

    last_time = Time::now();
    
    while(!m_window.should_close()){
        current_time = Time::now();
        delta_time = current_time - last_time;
        last_time = current_time;

        m_window.poll_events();
        update();
        render();
        m_gl.swap_buffers();
    }
}