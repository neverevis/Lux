#include <core/application.h>

Lux::Application::Application(i32 width, i32 height, const char* title)
    : window(width, height, title),
      gl(window)

{
    gl.make_current();
    window.show();
}

void Lux::Application::run(){
    loop();
}

void Lux::Application::loop(){
    while(!window.should_close()){
        window.poll_events();
        update(1);
        render();
        gl.swap_buffers();
    }
}