#include <graphics/gl.hpp>
#include "core/log.hpp"
#include "glcorearb.h"
#include "graphics/gl.hpp"
#include <graphics/vao.hpp>
#include <core/application.hpp>
#include <graphics/shader.hpp>
#include <stb_image.h>

namespace gl = Lux::Graphics::gl;
class Game : public Lux::Application{
public:
    Game(i32 w, i32 h, const char* title) 
        : Lux::Application(w, h, title)
        {}

    void setup(){
        GLuint vbo;
        gl::CreateBuffers(1, &vbo);
        std::vector<f32> vertices = {
            -0.5, -0.5, 0.0, 0.0,
            -0.5,  0.5, 0.0, 1.0,
             0.5,  0.5, 1.0, 1.0,
             0.5, -0.5, 1.0, 0.0
        };
        gl::NamedBufferStorage(vbo, vertices.size() * sizeof(f32), vertices.data(), GL_DYNAMIC_STORAGE_BIT);

        GLuint ebo;
        gl::CreateBuffers(1, &ebo);
        std::vector<u32> indices ={
            0,1,2,
            2,3,0
        };
        gl::NamedBufferStorage(ebo, indices.size() * sizeof(u32), indices.data(), GL_DYNAMIC_STORAGE_BIT);
        
        GLuint vao;
        gl::CreateVertexArrays(1, &vao);

        gl::VertexArrayVertexBuffer(vao, 0, vbo, 0, 4 * sizeof(f32));

        gl::EnableVertexArrayAttrib(vao, 0);
        gl::VertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
        gl::VertexArrayAttribBinding(vao, 0, 0);

        gl::EnableVertexArrayAttrib(vao, 1);
        gl::VertexArrayAttribFormat(vao, 1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32));
        gl::VertexArrayAttribBinding(vao, 1, 0);

        gl::VertexArrayElementBuffer(vao, ebo);

        
        Lux::Shader shader("a.vert", "a.frag");

        GLuint tex;
        gl::CreateTextures(GL_TEXTURE_2D, 1, &tex);
        gl::TextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        gl::TextureParameteri(tex, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, channels;

        stbi_set_flip_vertically_on_load(true);
        u8* data = stbi_load("assets/images/cat.jpg", &width, &height, &channels, 4);

        if(data){
            LUX_INFO("success!");
        }

        gl:Lux::Graphics::gl::TextureStorage2D(tex, 1, GL_RGBA8, width, height);
        gl::TextureSubImage2D(tex, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

        GLuint64 handle = gl::GetTextureHandleARB(tex);
        gl::MakeTextureHandleResidentARB(handle);

        GLuint instancing;
        gl::CreateBuffers(1, &instancing);
        gl::NamedBufferStorage(instancing, 8, &handle, GL_DYNAMIC_STORAGE_BIT);

        gl::VertexArrayVertexBuffer(vao, 1, instancing, 0, 8);
        gl::VertexArrayBindingDivisor(vao, 1, 1);

        gl::EnableVertexArrayAttrib(vao, 2);
        gl::VertexArrayAttribLFormat(vao, 2, 1, GL_UNSIGNED_INT64_ARB, 0);
        gl::VertexArrayAttribBinding(vao, 2, 1);

        gl::BindVertexArray(vao);
        shader.use();
    }

    void update(){
    }

    void render(){
        gl::ClearColor(0,0,0,1);
        gl::Clear(GL_COLOR_BUFFER_BIT);
        gl::DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
};

int main(){
    Game game(800,800,"game");
    game.run();
}