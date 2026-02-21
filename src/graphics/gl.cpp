#include "glcorearb.h"
#include <graphics/gl.hpp>
#include <platform/gl_loader.hpp>
#include <core/debug.hpp>

namespace Lux::Graphics::gl{
    PFNGLCLEARPROC                          Clear                           = nullptr;
    PFNGLCLEARCOLORPROC                     ClearColor                      = nullptr;
    PFNGLGETERRORPROC                       GetError                        = nullptr;
    
    PFNGLGETSTRINGIPROC                     GetStringi                      = nullptr;
    PFNGLGETINTEGERVPROC                    GetIntegerv                     = nullptr;

    PFNGLCREATESHADERPROC                   CreateShader                    = nullptr;
    PFNGLGETSHADERIVPROC                    GetShaderiv                     = nullptr;
    PFNGLSHADERSOURCEPROC                   ShaderSource                    = nullptr;
    PFNGLCOMPILESHADERPROC                  CompileShader                   = nullptr;
    PFNGLGETSHADERINFOLOGPROC               GetShaderInfoLog                = nullptr;
    PFNGLDELETESHADERPROC                   DeleteShader                    = nullptr;
    PFNGLCREATEPROGRAMPROC                  CreateProgram                   = nullptr;
    PFNGLATTACHSHADERPROC                   AttachShader                    = nullptr;
    PFNGLLINKPROGRAMPROC                    LinkProgram                     = nullptr;
    PFNGLGETPROGRAMIVPROC                   GetProgramiv                    = nullptr;
    PFNGLGETPROGRAMINFOLOGPROC              GetProgramInfoLog               = nullptr;
    
    PFNGLCREATETEXTURESPROC                 CreateTextures                  = nullptr;
    PFNGLTEXTURESTORAGE2DPROC               TextureStorage2D                = nullptr;
    PFNGLTEXTUREPARAMETERIPROC              TextureParameteri               = nullptr;
    PFNGLTEXTURESUBIMAGE2DPROC              TextureSubImage2D               = nullptr;
    PFNGLGETTEXTUREHANDLEARBPROC            GetTextureHandleARB             = nullptr;
    PFNGLMAKETEXTUREHANDLERESIDENTARBPROC   MakeTextureHandleResidentARB    = nullptr;

    using namespace Lux::Platform;
    bool init(){
        Clear       =                   (PFNGLCLEARPROC)                        load_gl_function("glClear");
        ClearColor  =                   (PFNGLCLEARCOLORPROC)                   load_gl_function("glClearColor");
        GetError    =                   (PFNGLGETERRORPROC)                     load_gl_function("glGetError");

        GetIntegerv =                   (PFNGLGETINTEGERVPROC)                  load_gl_function("glGetIntegerv");
        GetStringi  =                   (PFNGLGETSTRINGIPROC)                   load_gl_function("glGetStringi");

        CreateShader =                  (PFNGLCREATESHADERPROC)                 load_gl_function("glCreateShader");
        GetShaderiv =                   (PFNGLGETSHADERIVPROC)                  load_gl_function("glGetShaderiv");
        ShaderSource =                  (PFNGLSHADERSOURCEPROC)                 load_gl_function("glShaderSource");
        CompileShader =                 (PFNGLCOMPILESHADERPROC)                load_gl_function("glCompileShader");
        GetShaderInfoLog =              (PFNGLGETSHADERINFOLOGPROC)             load_gl_function("glGetShaderInfoLog");
        DeleteShader =                  (PFNGLDELETESHADERPROC)                 load_gl_function("glDeleteShader");
        CreateProgram =                 (PFNGLCREATEPROGRAMPROC)                load_gl_function("glCreateProgram");
        AttachShader =                  (PFNGLATTACHSHADERPROC)                 load_gl_function("glAttachShader");
        LinkProgram =                   (PFNGLLINKPROGRAMPROC)                  load_gl_function("glLinkProgram");
        GetProgramiv =                  (PFNGLGETPROGRAMIVPROC)                 load_gl_function("glGetProgramiv");
        GetProgramInfoLog =             (PFNGLGETPROGRAMINFOLOGPROC)            load_gl_function("glGetProgramInfoLog");

        CreateTextures =                (PFNGLCREATETEXTURESPROC)               load_gl_function("glCreateTextures");
        TextureStorage2D =              (PFNGLTEXTURESTORAGE2DPROC)             load_gl_function("glTextureStorage2D");
        TextureParameteri =             (PFNGLTEXTUREPARAMETERIPROC)            load_gl_function("glTextureParameteri");
        TextureSubImage2D =             (PFNGLTEXTURESUBIMAGE2DPROC)            load_gl_function("glTextureSubImage2D");
        GetTextureHandleARB =           (PFNGLGETTEXTUREHANDLEARBPROC)          load_gl_function("glGetTextureHandleARB");
        MakeTextureHandleResidentARB =  (PFNGLMAKETEXTUREHANDLERESIDENTARBPROC) load_gl_function("glMakeTextureHandleResidentARB");

        return true;
    }
}