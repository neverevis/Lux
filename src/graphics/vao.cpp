#include <graphics/data.hpp>
#include <graphics/vao.hpp>
#include <graphics/vbo.hpp>
#include <graphics/ebo.hpp>
#include <graphics/gl.hpp>

Lux::Graphics::VAO::VAO(){
    gl::CreateVertexArrays(1, &id_);
}

Lux::Graphics::VAO::~VAO(){
    gl::DeleteVertexArrays(1, &id_);
}

void Lux::Graphics::VAO::bind(){
    gl::BindVertexArray(id_);
}

void Lux::Graphics::VAO::link_vbo(const VBO& vbo, size_t stride, u32 binding_index) const{
    // stores a vbo in a binding index and sets a stride
    gl::VertexArrayVertexBuffer(id_, binding_index, vbo.id, 0, stride);
}

void Lux::Graphics::VAO::link_ebo(const EBO& ebo) const{
    gl::VertexArrayElementBuffer(id_, ebo.id);
}

void Lux::Graphics::VAO::set_location_format(u32 location, VertexType type, u32 count, u32 offset_count){
    GLenum gl_type = gl::to_gl_enum(type);

    size_t type_size;

    switch(type){
        case VertexType::Float32:
            type_size = sizeof(f32); break;
        case VertexType::Int32:
            type_size = sizeof(i32); break;
        case VertexType::Byte:
            type_size = 1; break;
        case VertexType::UnsignedByte:
            type_size = 1; break;
        case VertexType::Short16:
            type_size = sizeof(i16); break;
    }

    gl::EnableVertexArrayAttrib(id_, location);
    gl::VertexArrayAttribFormat(id_, location, count, gl_type, GL_FALSE, offset_count * type_size);
}

void Lux::Graphics::VAO::set_location_binding(u32 location , u32 binding_index){
    gl::VertexArrayAttribBinding(id_, location, binding_index);
}

void Lux::Graphics::VAO::set_binding_divisor(u32 binding_index, u32 divisor){
    gl::VertexArrayBindingDivisor(id_, binding_index, divisor);
}