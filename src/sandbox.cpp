#include "core/application.hpp"
#include <math/vector2.hpp>
#include <vector>

using namespace Lux;

class Sandbox : public Core::Application {
public:
    Sandbox(i32 width, i32 height, const char* title)
        : Application(width, height, title) {}

    void setup() override {
    }

    void update() override {
    }

    void render() override {
        const i32 total_instances = 100000;
        const i32 cols = 400;
        const f32 size = 1.0f;
        const f32 gap = 1.0f;

        for (i32 i = 0; i < total_instances; i++) {
            i32 x = i % cols;
            i32 y = i / cols;

            draw_rect(
                Math::Vector2{ (f32)x * (size + gap), (f32)y * (size + gap) }, 
                (u32)size, 
                (u32)size, 
                0.0f
            );
        }
    }
};

int main() {
    Sandbox sandbox(800, 800, "Lux - 100k Stress Test");
    sandbox.run();
}