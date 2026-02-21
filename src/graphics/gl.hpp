#pragma once
#include <glcorearb.h>

namespace Lux::Graphics::gl{
    extern PFNGLCLEARPROC       Clear;
    extern PFNGLCLEARCOLORPROC  ClearColor;
    extern PFNGLGETERRORPROC    GetError;

    extern PFNGLGETINTEGERVPROC GetIntegerv;
    extern PFNGLGETSTRINGIPROC  GetStringi;

    extern PFNGLCREATESHADERPROC CreateShader;
    extern PFNGLSHADERSOURCEPROC ShaderSource;
    extern PFNGLGETSHADERIVPROC GetShaderiv;
    extern PFNGLCREATEPROGRAMPROC CreateProgram;
    extern PFNGLATTACHSHADERPROC AttachShader;
    extern PFNGLLINKPROGRAMPROC LinkProgram;
    extern PFNGLGETPROGRAMIVPROC GetProgramiv;
    extern PFNGLGETPROGRAMINFOLOGPROC GetProgramInfoLog;

    extern PFNGLCREATETEXTURESPROC CreateTextures;
    extern PFNGLTEXTURESTORAGE2DPROC TextureStorage2D;
    extern PFNGLTEXTUREPARAMETERIPROC TextureParameteri;
    extern PFNGLTEXTURESUBIMAGE2DPROC TextureSubImage2D;
    extern PFNGLGETTEXTUREHANDLEARBPROC GetTextureHandleARB;
    extern PFNGLMAKETEXTUREHANDLERESIDENTARBPROC MakeTextureHandleResidentARB;

    bool init();

    #define GL_CHECK() \
    do { \
        GLenum err; \
        while((err = Lux::Graphics::gl::GetError()) != GL_NO_ERROR) { \
            printf("OpenGL error 0x%x at %s:%d\n", err, __FILE__, __LINE__); \
        } \
    } while(0)
}