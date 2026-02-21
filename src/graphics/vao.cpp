#include "graphics/gl.hpp"
#include <graphics/vao.hpp>

namespace gl = Lux::Graphics::gl;
Lux::VAO::VAO(){
    gl::CreateVertexArrays(1, &id_);
}

Lux::VAO::~VAO(){

}

void Lux::VAO::bind(){
    gl::BindVertexArray(id_);
}

void Lux::VAO::link_vbo(VBO& vbo, size_t vertex_size){
    gl::VertexArrayVertexBuffer(id_, 0, vbo.id, 0, vertex_size);
}

void Lux::VAO::set_location(GLuint location, GLint data_type, GLuint size, GLuint offset){
    gl::EnableVertexArrayAttrib(id_, location);
    gl::VertexArrayAttribFormat(id_, location, size, data_type, GL_FALSE, offset);
    gl::VertexArrayAttribBinding(id_, location, 0);
}