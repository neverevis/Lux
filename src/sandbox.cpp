#include "core/application.hpp"
#include "core/types.hpp"

class Sandbox : public Lux::Application{
public:
    Sandbox(i32 width, i32 height, const char* title)
        : Application(width, height, title)
        {} 

    ~Sandbox() = default;

    void setup(){

    }

    void update(){

    }

    void render(){

    }
};

int main(){
    Sandbox sandbox(800,800,"sandbox");
    sandbox.run();
}