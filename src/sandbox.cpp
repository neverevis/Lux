#include <core/application.hpp>
#include <math/vector2.hpp>
#include <vector>
#define COPIES 10
#define SPACE 800/COPIES

using namespace Lux;

class Sandbox : public Core::Application {
public:
    f32 rotation = 0;

    Sandbox(i32 width, i32 height, const char* title)
        : Application(width, height, title) {}

    void setup() override {
    }

    void update() override {
    }

    void render() override {
        draw_rect({400,400}, 100, 100, rotation, {0.5,0.5});
        rotation += delta_time.as_seconds() * 70;
    }
};

int main() {
    Sandbox sandbox(800, 800, "lux");
    sandbox.run();
}