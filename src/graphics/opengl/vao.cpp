#include <graphics/opengl/vao.hpp>
#include <graphics/opengl/vbo.hpp>
#include <graphics/opengl/ebo.hpp>

Lux::Graphics::OpenGL::VAO::VAO(){
    gl::CreateVertexArrays(1, &id_);
}

Lux::Graphics::OpenGL::VAO::~VAO(){
    gl::DeleteVertexArrays(1, &id_);
}

void Lux::Graphics::OpenGL::VAO::bind(){
    gl::BindVertexArray(id_);
}

void Lux::Graphics::OpenGL::VAO::link_vbo(VBO& vbo, size_t stride, GLint binding_index){
    // stores a vbo in a binding index and sets a stride
    gl::VertexArrayVertexBuffer(id_, binding_index, vbo.id, 0, stride);
}

void Lux::Graphics::OpenGL::VAO::link_ebo(EBO& ebo){
    gl::VertexArrayElementBuffer(id_, ebo.id);
}

void Lux::Graphics::OpenGL::VAO::location_format(GLint location, GLenum type, GLuint quantity){
    gl::EnableVertexArrayAttrib(id_, location);
    gl::VertexArrayAttribFormat(id_, location, quantity, type, GL_FALSE, 0);
}

void Lux::Graphics::OpenGL::VAO::set_location_binding(GLint location ,GLint binding_index){
    gl::VertexArrayAttribBinding(id_, location, binding_index);
}

void Lux::Graphics::OpenGL::VAO::set_binding_divisor(GLint binding_index, GLuint divisor){
    gl::VertexArrayBindingDivisor(id_, binding_index, divisor);
}