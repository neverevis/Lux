#include "core/application.hpp"
#include "core/types.hpp"
#include <graphics/gl.hpp>

class Sandbox : public Lux::Application{
public:
    Sandbox(i32 width, i32 height, const char* title)
        : Application(width, height, title)
        {} 

    ~Sandbox() = default;

    void setup(){
    }

    void update(){
        GL_CHECK();
    }

    void render(){
        render_quad();
    }
};

int main(){
    Sandbox sandbox(800,800,"sandbox");
    sandbox.run();
}