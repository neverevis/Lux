#include "platform/window.h"


int main(){
    Lux::Window window(800,800,"test");

    while(true){
        window.poll_events();
    }
}