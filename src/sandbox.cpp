#include <core/application.hpp>
#include <graphics/opengl/gl.hpp>
#include <graphics/opengl/vbo.hpp>
#include <graphics/opengl/ebo.hpp>
#include <graphics/opengl/vao.hpp>
#include <graphics/opengl/shader.hpp>
#include <stb_image.h>

void convert_to_ndc(f32* vertices, size_t size);
namespace gl = Lux::Graphics::OpenGL::gl;
class Game : public Lux::Application{
public:
    Lux::Graphics::OpenGL::VBO quad_vbo;
    Lux::Graphics::OpenGL::VBO pos_vbo;
    Lux::Graphics::OpenGL::EBO quad_ebo;
    Lux::Graphics::OpenGL::VAO vao;
    Lux::Graphics::OpenGL::Shader shader;



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

        f32 positions[] = {
            400,400,
            700,400,
            100,400,
            700,700,
            100,100
        };

        convert_to_ndc(positions, sizeof(positions));

        pos_vbo.set_size(sizeof(positions));
        pos_vbo.submit_data(positions, sizeof(positions), 0);

        vao.link_vbo(pos_vbo, 2 * sizeof(f32), 1);
        vao.location_format(1, GL_FLOAT, 2);
        vao.set_location_binding(1, 1);
        vao.set_binding_divisor(1, 1);

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
        gl::DrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, 5);
        GL_CHECK();
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