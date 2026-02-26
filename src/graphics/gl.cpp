#include "glcorearb.h"
#include <graphics/gl.hpp>
#include <core/debug.hpp>

namespace Lux::Graphics::gl{
    bool loaded = false;

    PFNGLCLEARPROC                          Clear                           = nullptr;
    PFNGLCLEARCOLORPROC                     ClearColor                      = nullptr;
    PFNGLGETERRORPROC                       GetError                        = nullptr;
    PFNGLDISABLEPROC                        Disable                         = nullptr;
    
    PFNGLGETSTRINGIPROC                     GetStringi                      = nullptr;
    PFNGLGETINTEGERVPROC                    GetIntegerv                     = nullptr;
    PFNGLGETUNIFORMLOCATIONPROC             GetUniformLocation              = nullptr;

    PFNGLUNIFORMMATRIX4FVPROC               UniformMatrix4fv                = nullptr;

    PFNGLCREATEBUFFERSPROC                  CreateBuffers                   = nullptr;
    PFNGLNAMEDBUFFERSTORAGEPROC             NamedBufferStorage              = nullptr;
    PFNGLNAMEDBUFFERSUBDATAPROC             NamedBufferSubData              = nullptr;
    PFNGLDELETEBUFFERSPROC                  DeleteBuffers                   = nullptr;
    PFNGLMAPNAMEDBUFFERRANGEPROC            MapNamedBufferRange             = nullptr;

    PFNGLCREATEVERTEXARRAYSPROC             CreateVertexArrays              = nullptr;
    PFNGLVERTEXARRAYVERTEXBUFFERPROC        VertexArrayVertexBuffer         = nullptr;
    PFNGLENABLEVERTEXARRAYATTRIBEXTPROC     EnableVertexArrayAttrib         = nullptr;
    PFNGLVERTEXARRAYATTRIBFORMATPROC        VertexArrayAttribFormat         = nullptr;
    PFNGLVERTEXARRAYATTRIBLFORMATPROC       VertexArrayAttribLFormat        = nullptr;
    PFNGLVERTEXARRAYATTRIBBINDINGPROC       VertexArrayAttribBinding        = nullptr;
    PFNGLBINDVERTEXARRAYPROC                BindVertexArray                 = nullptr;
    PFNGLVERTEXARRAYBINDINGDIVISORPROC      VertexArrayBindingDivisor       = nullptr;
    PFNGLVERTEXARRAYELEMENTBUFFERPROC       VertexArrayElementBuffer        = nullptr;
    PFNGLDELETEVERTEXARRAYSPROC             DeleteVertexArrays              = nullptr;

    PFNGLDRAWARRAYSPROC                     DrawArrays                      = nullptr;
    PFNGLDRAWELEMENTSPROC                   DrawElements                    = nullptr;
    PFNGLDRAWARRAYSINSTANCEDPROC            DrawArraysInstanced             = nullptr;
    PFNGLDRAWELEMENTSINSTANCEDPROC          DrawElementsInstanced           = nullptr;

    PFNGLCREATESHADERPROC                   CreateShader                    = nullptr;
    PFNGLGETSHADERIVPROC                    GetShaderiv                     = nullptr;
    PFNGLSHADERSOURCEPROC                   ShaderSource                    = nullptr;
    PFNGLCOMPILESHADERPROC                  CompileShader                   = nullptr;
    PFNGLGETSHADERINFOLOGPROC               GetShaderInfoLog                = nullptr;
    PFNGLDELETESHADERPROC                   DeleteShader                    = nullptr;
    PFNGLCREATEPROGRAMPROC                  CreateProgram                   = nullptr;
    PFNGLATTACHSHADERPROC                   AttachShader                    = nullptr;
    PFNGLLINKPROGRAMPROC                    LinkProgram                     = nullptr;
    PFNGLUSEPROGRAMPROC                     UseProgram                      = nullptr;
    PFNGLGETPROGRAMIVPROC                   GetProgramiv                    = nullptr;
    PFNGLGETPROGRAMINFOLOGPROC              GetProgramInfoLog               = nullptr;
    PFNGLDELETEPROGRAMPROC                  DeleteProgram                   = nullptr;
    
    PFNGLCREATETEXTURESPROC                 CreateTextures                  = nullptr;
    PFNGLTEXTURESTORAGE2DPROC               TextureStorage2D                = nullptr;
    PFNGLTEXTUREPARAMETERIPROC              TextureParameteri               = nullptr;
    PFNGLTEXTURESUBIMAGE2DPROC              TextureSubImage2D               = nullptr;
    PFNGLGETTEXTUREHANDLEARBPROC            GetTextureHandleARB             = nullptr;
    PFNGLMAKETEXTUREHANDLERESIDENTARBPROC   MakeTextureHandleResidentARB    = nullptr;

    bool init(void* (*get_fn_address)(const char* fn_name)){
        #define LOAD_GL_FN(fn, name) fn = (decltype(fn)) get_fn_address(name)

        LOAD_GL_FN(Clear,"glClear");
        LOAD_GL_FN(ClearColor, "glClearColor");
        LOAD_GL_FN(GetError,"glGetError");
        LOAD_GL_FN(Disable, "glDisable");

        LOAD_GL_FN(GetStringi,"glGetStringi");
        LOAD_GL_FN(GetIntegerv,"glGetIntegerv");
        LOAD_GL_FN(GetUniformLocation,"glGetUniformLocation");

        LOAD_GL_FN(UniformMatrix4fv,"glUniformMatrix4fv");

        LOAD_GL_FN(CreateBuffers,"glCreateBuffers");
        LOAD_GL_FN(NamedBufferStorage,"glNamedBufferStorage");
        LOAD_GL_FN(NamedBufferSubData,"glNamedBufferSubData");
        LOAD_GL_FN(DeleteBuffers,"glDeleteBuffers");
        LOAD_GL_FN(MapNamedBufferRange,"glMapNamedBufferRange");

        LOAD_GL_FN(CreateVertexArrays,"glCreateVertexArrays");
        LOAD_GL_FN(VertexArrayVertexBuffer,"glVertexArrayVertexBuffer");
        LOAD_GL_FN(EnableVertexArrayAttrib,"glEnableVertexArrayAttrib");
        LOAD_GL_FN(VertexArrayAttribFormat,"glVertexArrayAttribFormat");
        LOAD_GL_FN(VertexArrayAttribLFormat, "glVertexArrayAttribLFormat");
        LOAD_GL_FN(VertexArrayAttribBinding,"glVertexArrayAttribBinding");
        LOAD_GL_FN(BindVertexArray,"glBindVertexArray");
        LOAD_GL_FN(VertexArrayBindingDivisor, "glVertexArrayBindingDivisor");
        LOAD_GL_FN(VertexArrayElementBuffer, "glVertexArrayElementBuffer");
        LOAD_GL_FN(DeleteVertexArrays, "glDeleteVertexArrays");

        LOAD_GL_FN(DrawArrays,"glDrawArrays");
        LOAD_GL_FN(DrawElements,"glDrawElements");
        LOAD_GL_FN(DrawArraysInstanced, "glDrawArraysInstanced");
        LOAD_GL_FN(DrawElementsInstanced,"glDrawElementsInstanced");

        LOAD_GL_FN(CreateShader,"glCreateShader");
        LOAD_GL_FN(GetShaderiv,"glGetShaderiv");
        LOAD_GL_FN(ShaderSource,"glShaderSource");
        LOAD_GL_FN(CompileShader,"glCompileShader");
        LOAD_GL_FN(GetShaderInfoLog,"glGetShaderInfoLog");
        LOAD_GL_FN(DeleteShader,"glDeleteShader");
        LOAD_GL_FN(CreateProgram,"glCreateProgram");
        LOAD_GL_FN(AttachShader,"glAttachShader");
        LOAD_GL_FN(LinkProgram,"glLinkProgram");
        LOAD_GL_FN(UseProgram,"glUseProgram");
        LOAD_GL_FN(GetProgramiv,"glGetProgramiv");
        LOAD_GL_FN(GetProgramInfoLog,"glGetProgramInfoLog");
        LOAD_GL_FN(DeleteProgram,"glDeleteProgram");

        LOAD_GL_FN(CreateTextures,"glCreateTextures");
        LOAD_GL_FN(TextureStorage2D,"glTextureStorage2D");
        LOAD_GL_FN(TextureParameteri,"glTextureParameteri");
        LOAD_GL_FN(TextureSubImage2D,"glTextureSubImage2D");
        LOAD_GL_FN(GetTextureHandleARB,"glGetTextureHandleARB");
        LOAD_GL_FN(MakeTextureHandleResidentARB,"glMakeTextureHandleResidentARB");

        loaded = true;
        #undef LOAD_GL_FN
        return true;
    }

    GLenum to_gl_enum(VertexType type){
        switch(type){
            case VertexType::Float32:
                return GL_FLOAT;
            case VertexType::Int32:
                return GL_INT;
            case VertexType::Byte:
                return GL_BYTE;
            case VertexType::UnsignedByte:
                return GL_UNSIGNED_BYTE;
            case VertexType::Short16:
                return GL_SHORT;
        }
    }
}