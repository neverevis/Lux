#include <graphics/vbo.hpp>

namespace gl = Lux::Graphics::gl;
Lux::VBO::VBO(std::vector<float>& vertices){
    gl::CreateBuffers(1, &id_);
    gl::NamedBufferStorage(id_, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_DYNAMIC_STORAGE_BIT);
}

Lux::VBO::~VBO(){
    if(id_ != 0)
        gl::DeleteBuffers(1, &id_);
}