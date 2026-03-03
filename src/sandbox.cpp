#include "core/input.hpp"
#include "math/vector3.hpp"
#include <core/application.hpp>
#include <math/vector2.hpp>
#include <vector>
#define COPIES 10
#define SPACE 800/COPIES

using namespace Lux;

class Sandbox : public Core::Application {
public:
    f32 rotation = 0;

    Math::Vector3 cam_pos;
    Math::Vector3 dir;

    Math::Vector3 velocity;

    f32 speed = 5;

    Sandbox(i32 width, i32 height, const char* title)
        : Application(width, height, title) {}

    void setup() override {
        cam_pos.z = 3;
    }

    void update() override {
        dir.reset();
        if(Core::Input::key_pressed(Core::Keyboard::Key::W)){
            dir.z--;
        }
        if(Core::Input::key_pressed(Core::Keyboard::Key::A)){
            dir.x++;
        }
        if(Core::Input::key_pressed(Core::Keyboard::Key::S)){
            dir.z++;
        }
        if(Core::Input::key_pressed(Core::Keyboard::Key::D)){
            dir.x--;
        }

        dir = dir.normalized();

        velocity = dir * speed * delta_time.as_seconds();
        velocity*= 0.9;

        cam_pos += velocity;

        set_camera_position(cam_pos);
    }

    void render() override {
        draw_rect({0,0}, 1, 1, rotation, {0.5,0.5});
        rotation += delta_time.as_seconds() * 70;
    }
};

int main() {
    Sandbox sandbox(800, 800, "lux");
    sandbox.run();
}