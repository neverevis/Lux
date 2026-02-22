#include <graphics/gl.hpp>
#include "glcorearb.h"
#include "graphics/gl.hpp"
#include <graphics/vao.hpp>
#include <core/application.hpp>
#include <graphics/shader.hpp>
#include <stb_image.h>

void convert_to_ndc(f32* vertices, size_t size);
namespace gl = Lux::Graphics::gl;
class Game : public Lux::Application{
public:
    Lux::VBO quad_vbo;
    Lux::EBO quad_ebo;
    Lux::VAO vao;
    Lux::Shader shader;



    Game(i32 w, i32 h, const char* title) 
        : Lux::Application(w, h, title)
        , shader("src/shaders/a.vert","src/shaders/a.frag")
        {}

    void setup(){
        f32 quad_vertices[] = {
            300,300,
            300,500,
            500,500,
            500,300
        };

        convert_to_ndc(quad_vertices, sizeof(quad_vertices));

        quad_vbo.set_size(sizeof(quad_vertices));
        quad_vbo.submit_data(quad_vertices, sizeof(quad_vertices), 0);

        i32 quad_indices[] = {
            0,1,2,
            2,3,0
        };

        quad_ebo.set_size(sizeof(quad_indices));
        quad_ebo.submit_data(quad_indices, sizeof(quad_indices), 0);

        vao.link_vbo(quad_vbo, 2 * sizeof(f32), 0);
        vao.link_ebo(quad_ebo);

        vao.location_format(0, GL_FLOAT, 2);
        vao.set_location_binding(0, 0);

        shader.use();
        vao.bind();
    }

    void update(){
    }

    void render(){
        gl::ClearColor(0,1,1,1);
        gl::Clear(GL_COLOR_BUFFER_BIT);
        gl::DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
};

int main(){
    Game game(800,800,"game");
    game.run();
}

void convert_to_ndc(f32* vertices, size_t size){
    for(int i = 0; i < size/4; i++){
        vertices[i] = (vertices[i] * 2 / 800) - 1;
    }
}