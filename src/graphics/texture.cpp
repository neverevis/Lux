#include <graphics/texture.hpp>
#include <graphics/gl.hpp>

Lux::Graphics::Texture::Texture(const char* source_path)
    : id(id_)
{
    gl::CreateTextures(GL_TEXTURE_2D, 1, &id_);
}