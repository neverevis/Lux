#include <platform/window.h>
#include <platform/gl_context.h>
#include <print>
int main(){
    Lux::Window window(800, 800, "Lux Engine");
    Lux::GLContext gl(window);
    gl.make_current();
    window.show();

    while(!window.should_close()){
        window.poll_events();
        gl.swap_buffers();
    }
}