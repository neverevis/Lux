#include "core/application.hpp"
#include <math/vector2.hpp>
#include <vector>
#define COPIES 10
#define SPACE 800/COPIES

using namespace Lux;

class Sandbox : public Core::Application {
public:
    f32 rotation = 0;
    f32 incremental = 0;

    Sandbox(i32 width, i32 height, const char* title)
        : Application(width, height, title) {}

    void setup() override {
    }

    void update() override {
    }

    void render() override {
        for(int i = 0; i < 400; i++){
            for(int j = 0; j < 400; j++){
                draw_rect({(f32)(i*2.0f)+ sinf(incremental + j)*20,(f32)(j*2.0f) + sinf(incremental + i)*20}, 2, 2,
                (i % 2 == 0 ? sinf(incremental)*30 : sinf(-incremental)*30),
                {0.5f, 0.5f});
            }
        }
        rotation += delta_time.as_seconds() * 10;
        incremental += 3 * delta_time.as_seconds();
    }
};

int main() {
    Sandbox sandbox(800, 800, "lux");
    sandbox.run();
}