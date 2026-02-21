#include "graphics/gl.hpp"
#include "graphics/vbo.hpp"
#include <graphics/vao.hpp>
#include <core/application.hpp>
#include <graphics/shader.hpp>

namespace gl = Lux::Graphics::gl;
class Game : public Lux::Application{
public:

    std::vector<f32> vertices;
    Lux::Shader shader;
    Lux::VBO vbo;
    Lux::VAO vao;


    Game(i32 w, i32 h, const char* title) 
        : Lux::Application(w, h, title)
        , vertices({
            -0.5,-0.5, 1,0,0,
            0.5,-0.5, 0,1,0,
            -0.5,0.5, 0,0,1,
            -0.5,0.5,1,0,0,
            0.5,0.5,0,1,0,
            0.5,-0.5,0,0,1
        })
        , vbo(vertices)
        , shader("a.vert", "a.frag")
        {}

    void setup(){
        vao.link_vbo(vbo, sizeof(f32) * 5);
        vao.set_location(0, GL_FLOAT, 2, 0);
        vao.set_location(1, GL_FLOAT, 3, 2 * sizeof(f32));

        GL_CHECK();

    }

    void update(){
    }

    void render(){
        gl::ClearColor(0,0,0,1);
        gl::Clear(GL_COLOR_BUFFER_BIT);
        vao.bind();
        shader.use();
        gl::DrawArrays(GL_TRIANGLES, 0, 6);

        GL_CHECK();
    }
};

int main(){
    Game game(800,800,"game");
    game.run();
}