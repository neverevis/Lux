#include <gl/shader.h>
#include <core/types.h>
#include <core/utils.h>

Lux::Shader::Shader(const char* vert_path, const char* frag_path){
    char vert_src[1024];
    char frag_src[1024];

    Lux::Utils::read_file(vert_path, vert_src);
    Lux::Utils::read_file(vert_path, frag_src);
}