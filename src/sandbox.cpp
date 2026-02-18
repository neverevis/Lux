#include "platform/gl_context.h"
#include <platform/window.h>
#include <print>

int main(){
    Lux::Window window(800,800,"window");
    Lux::GLContext context(window);
    context.make_current();
    window.show();

    while(!window.should_close()){
        window.poll_events();
    }
}