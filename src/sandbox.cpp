#include "core/application.hpp"
#include "core/log.hpp"
#include "core/types.hpp"
#include "graphics/mesh.hpp"
#include "memory/static_pool.hpp"
#include <graphics/gl.hpp>
#include <math/matrix4.hpp>
#include <math/vector2.hpp>

namespace gl = Lux::Graphics::gl;
class Sandbox : public Lux::Core::Application{
public:
    f32 degrees = 0;


    Sandbox(i32 width, i32 height, const char* title)
        : Application(width, height, title)
        {} 

    ~Sandbox() = default;

    void setup(){
    }

    void update(){
        degrees += 360 * delta_time.as_seconds();
        GL_CHECK();
    }

    void render(){
        draw_rect({400 - 50,400 - 50},200,200, degrees);
    }
};

int main(){
    Sandbox sandbox(800,800,"sandbox");
    sandbox.run();
}