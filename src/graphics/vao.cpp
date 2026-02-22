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

void Lux::VAO::link_vbo(VBO& vbo, size_t vertex_size, GLint binding_index){
    // put the VBO into a specific binding index inside this VAO. also set the binding index stride (how many bytes represents a single vertex)
    gl::VertexArrayVertexBuffer(id_, binding_index, vbo.id, 0, vertex_size);
}

void Lux::VAO::set_location(GLuint location, GLint data_type, GLuint size, GLuint offset, GLint binding_index){
    // activates the location on shader
    gl::EnableVertexArrayAttrib(id_, location);
    // describes how the location should interpret and take VBO vertices contained in a binding index
    gl::VertexArrayAttribFormat(id_, location, size, data_type, GL_FALSE, offset);
    //  sets which binding index the location should take the VBO from
    gl::VertexArrayAttribBinding(id_, location, binding_index);
}

void Lux::VAO::set_divisor(GLuint location, GLint binding_index, GLuint divisor){
    //sets a binding index as divisor (should only step next once all the vertices iterates)
    gl::VertexArrayBindingDivisor(id_, binding_index, divisor);
}