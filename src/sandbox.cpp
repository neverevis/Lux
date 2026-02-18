#include <platform/window.h>

int main(){
    Lux::Window window(800,800,"window");
    window.show();

    while(!window.should_close()){
        window.poll_events();
    }
}