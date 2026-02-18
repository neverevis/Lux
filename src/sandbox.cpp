#include "glcorearb.h"
#include "platform/gl_context.h"
#include "platform/gl_renderer.h"
#include <platform/window.h>
#include <print>

int main(){
    Lux::Window window(800,800,"window");
    Lux::GLContext context(window);
    context.make_current();
    Lux::GLRenderer::init();
    window.show();


    Lux::GLRenderer::ClearColor(1,0,0,1);
    while(!window.should_close()){
        window.poll_events();
        Lux::GLRenderer::Clear(GL_COLOR_BUFFER_BIT);
        context.swap_buffers();
    }
}