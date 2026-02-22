#include "graphics/gl.hpp"
#include <graphics/vao.hpp>

namespace gl = Lux::Graphics::gl;
Lux::VAO::VAO(){
    gl::CreateVertexArrays(1, &id_);
}

Lux::VAO::~VAO(){
    gl::DeleteVertexArrays(1, &id_);
}

void Lux::VAO::bind(){
    gl::BindVertexArray(id_);
}

void Lux::VAO::link_vbo(VBO& vbo, size_t stride, GLint binding_index){
    // stores a vbo in a binding index and sets a stride
    gl::VertexArrayVertexBuffer(id_, binding_index, vbo.id, 0, stride);
}

void Lux::VAO::link_ebo(EBO& ebo){
    gl::VertexArrayElementBuffer(id_, ebo.id);
}

void Lux::VAO::location_format(GLint location, GLenum type, GLuint quantity){
    gl::EnableVertexArrayAttrib(id_, location);
    gl::VertexArrayAttribFormat(id_, location, quantity, type, GL_FALSE, 0);
}

void Lux::VAO::set_location_binding(GLint location ,GLint binding_index){
    gl::VertexArrayAttribBinding(id_, location, binding_index);
}

void Lux::VAO::set_binding_divisor(GLint binding_index, GLuint divisor){
    gl::VertexArrayBindingDivisor(id_, binding_index, divisor);
}