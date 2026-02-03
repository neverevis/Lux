#include <platform/window.h>
#include <print>
int main(){
    Lux::Window window(800, 800, "Lux Engine");
    window.show();

    while(!window.should_close()){
        window.poll_events();
    }
}