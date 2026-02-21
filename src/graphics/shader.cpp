#include "core/log.hpp"
#include "glcorearb.h"
#include <graphics/shader.hpp>
#include <graphics/gl.hpp>
#include <core/types.hpp>
#include <core/debug.hpp>

#include <string>
#include <fstream>
#include <sstream>

std::string get_source_str(const char* path){
    std::ifstream file(path, std::ios::binary);
    LUX_VERIFY(file.is_open(), "couldn't find {}", path);

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

namespace gl = Lux::Graphics::gl;
Lux::Shader::Shader(const char* vert_path, const char* frag_path){
    GLuint v_shader = gl::CreateShader(GL_VERTEX_SHADER);
    GLuint f_shader = gl::CreateShader(GL_FRAGMENT_SHADER);

    std::string v_src = get_source_str(vert_path);
    std::string f_src = get_source_str(frag_path);

    const char* v_ptr = v_src.c_str();
    const char* f_ptr = f_src.c_str();
    
    gl::ShaderSource(v_shader, 1, &v_ptr, nullptr);
    gl::ShaderSource(f_shader, 1, &f_ptr, nullptr);

    gl::CompileShader(v_shader);
    check_shader_errors(v_shader);
    gl::CompileShader(f_shader);
    check_shader_errors(f_shader);

    id_ = gl::CreateProgram();

    gl::AttachShader(id_, v_shader);
    gl::AttachShader(id_, f_shader);

    gl::LinkProgram(id_);

    gl::DeleteShader(v_shader);
    gl::DeleteShader(f_shader);

}

Lux::Shader::~Shader(){
}

void Lux::Shader::use(){
    gl::UseProgram(id_);
}

void Lux::Shader::check_shader_errors(GLuint shader){
    GLint success;
    
    gl::GetShaderiv(shader, GL_COMPILE_STATUS, &success);

    LUX_INFO("{}",success);

    if(success != GL_TRUE){
        GLchar info_log[512];

        gl::GetShaderInfoLog(shader, 512, nullptr, info_log);
        LUX_ERROR("{}", info_log);
    }
}