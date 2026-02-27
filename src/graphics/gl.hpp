#pragma once

#include <glcorearb.h>
#include <core/debug.hpp>
#include <graphics/data.hpp>

namespace Lux::Graphics::gl{
    extern bool loaded;

    extern PFNGLCLEARPROC                          Clear                           ;
    extern PFNGLCLEARCOLORPROC                     ClearColor                      ;
    extern PFNGLGETERRORPROC                       GetError                        ;
    extern PFNGLDISABLEPROC                        Disable;
    
    extern PFNGLGETSTRINGIPROC                     GetStringi                      ;
    extern PFNGLGETINTEGERVPROC                    GetIntegerv                     ;
    extern PFNGLGETUNIFORMLOCATIONPROC             GetUniformLocation;

    extern PFNGLUNIFORMMATRIX4FVPROC               UniformMatrix4fv;

    extern PFNGLCREATEBUFFERSPROC                  CreateBuffers                   ;
    extern PFNGLNAMEDBUFFERSTORAGEPROC             NamedBufferStorage              ;
    extern PFNGLNAMEDBUFFERSUBDATAPROC             NamedBufferSubData;
    extern PFNGLDELETEBUFFERSPROC                  DeleteBuffers;
    extern PFNGLMAPNAMEDBUFFERRANGEPROC            MapNamedBufferRange;

    extern PFNGLCREATEVERTEXARRAYSPROC             CreateVertexArrays              ;
    extern PFNGLVERTEXARRAYVERTEXBUFFERPROC        VertexArrayVertexBuffer         ;
    extern PFNGLENABLEVERTEXARRAYATTRIBEXTPROC     EnableVertexArrayAttrib         ;
    extern PFNGLVERTEXARRAYATTRIBFORMATPROC        VertexArrayAttribFormat         ;
    extern PFNGLVERTEXARRAYATTRIBLFORMATPROC       VertexArrayAttribLFormat;
    extern PFNGLVERTEXARRAYATTRIBBINDINGPROC       VertexArrayAttribBinding        ;
    extern PFNGLBINDVERTEXARRAYPROC                BindVertexArray                 ;
    extern PFNGLVERTEXARRAYBINDINGDIVISORPROC      VertexArrayBindingDivisor;
    extern PFNGLVERTEXARRAYELEMENTBUFFERPROC       VertexArrayElementBuffer;
    extern PFNGLDELETEVERTEXARRAYSPROC             DeleteVertexArrays;

    extern PFNGLDRAWARRAYSPROC                     DrawArrays                      ;
    extern PFNGLDRAWELEMENTSPROC                   DrawElements;
    extern PFNGLDRAWARRAYSINSTANCEDPROC            DrawArraysInstanced;
    extern PFNGLDRAWELEMENTSINSTANCEDPROC          DrawElementsInstanced;
    extern PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC DrawElementsInstancedBaseInstance;

    extern PFNGLCREATESHADERPROC                   CreateShader                    ;
    extern PFNGLGETSHADERIVPROC                    GetShaderiv                     ;
    extern PFNGLSHADERSOURCEPROC                   ShaderSource                    ;
    extern PFNGLCOMPILESHADERPROC                  CompileShader                   ;
    extern PFNGLGETSHADERINFOLOGPROC               GetShaderInfoLog                ;
    extern PFNGLDELETESHADERPROC                   DeleteShader                    ;
    extern PFNGLCREATEPROGRAMPROC                  CreateProgram                   ;
    extern PFNGLATTACHSHADERPROC                   AttachShader                    ;
    extern PFNGLLINKPROGRAMPROC                    LinkProgram                     ;
    extern PFNGLUSEPROGRAMPROC                     UseProgram                      ;
    extern PFNGLGETPROGRAMIVPROC                   GetProgramiv                    ;
    extern PFNGLGETPROGRAMINFOLOGPROC              GetProgramInfoLog               ;
    extern PFNGLDELETEPROGRAMPROC                  DeleteProgram;
    
    extern PFNGLCREATETEXTURESPROC                 CreateTextures                  ;
    extern PFNGLTEXTURESTORAGE2DPROC               TextureStorage2D                ;
    extern PFNGLTEXTUREPARAMETERIPROC              TextureParameteri               ;
    extern PFNGLTEXTURESUBIMAGE2DPROC              TextureSubImage2D               ;
    extern PFNGLGETTEXTUREHANDLEARBPROC            GetTextureHandleARB             ;
    extern PFNGLMAKETEXTUREHANDLERESIDENTARBPROC   MakeTextureHandleResidentARB    ;

    bool init(void* (*get_fn_address)(const char* fn_name));

    GLenum to_gl_enum(VertexType type);

    #define GL_CHECK() \
    do { \
        GLenum err; \
        while((err = Lux::Graphics::gl::GetError()) != GL_NO_ERROR) { \
            LUX_INFO("OpenGL error {}", err); \
        } \
    } while(0)
}