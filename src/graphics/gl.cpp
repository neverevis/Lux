#include "glcorearb.h"
#include <graphics/gl.hpp>
#include <core/debug.hpp>

namespace Lux::Graphics::gl{
    bool loaded = false;

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

    bool init(void* (*get_fn_address)(const char* fn_name)){
        Clear       =                   (PFNGLCLEARPROC)                        get_fn_address("glClear");
        ClearColor  =                   (PFNGLCLEARCOLORPROC)                   get_fn_address("glClearColor");
        GetError    =                   (PFNGLGETERRORPROC)                     get_fn_address("glGetError");
        
        GetIntegerv =                   (PFNGLGETINTEGERVPROC)                  get_fn_address("glGetIntegerv");
        GetStringi  =                   (PFNGLGETSTRINGIPROC)                   get_fn_address("glGetStringi");

        CreateShader =                  (PFNGLCREATESHADERPROC)                 get_fn_address("glCreateShader");
        GetShaderiv =                   (PFNGLGETSHADERIVPROC)                  get_fn_address("glGetShaderiv");
        ShaderSource =                  (PFNGLSHADERSOURCEPROC)                 get_fn_address("glShaderSource");
        CompileShader =                 (PFNGLCOMPILESHADERPROC)                get_fn_address("glCompileShader");
        GetShaderInfoLog =              (PFNGLGETSHADERINFOLOGPROC)             get_fn_address("glGetShaderInfoLog");
        DeleteShader =                  (PFNGLDELETESHADERPROC)                 get_fn_address("glDeleteShader");
        CreateProgram =                 (PFNGLCREATEPROGRAMPROC)                get_fn_address("glCreateProgram");
        AttachShader =                  (PFNGLATTACHSHADERPROC)                 get_fn_address("glAttachShader");
        LinkProgram =                   (PFNGLLINKPROGRAMPROC)                  get_fn_address("glLinkProgram");
        GetProgramiv =                  (PFNGLGETPROGRAMIVPROC)                 get_fn_address("glGetProgramiv");
        GetProgramInfoLog =             (PFNGLGETPROGRAMINFOLOGPROC)            get_fn_address("glGetProgramInfoLog");

        CreateTextures =                (PFNGLCREATETEXTURESPROC)               get_fn_address("glCreateTextures");
        TextureStorage2D =              (PFNGLTEXTURESTORAGE2DPROC)             get_fn_address("glTextureStorage2D");
        TextureParameteri =             (PFNGLTEXTUREPARAMETERIPROC)            get_fn_address("glTextureParameteri");
        TextureSubImage2D =             (PFNGLTEXTURESUBIMAGE2DPROC)            get_fn_address("glTextureSubImage2D");
        GetTextureHandleARB =           (PFNGLGETTEXTUREHANDLEARBPROC)          get_fn_address("glGetTextureHandleARB");
        MakeTextureHandleResidentARB =  (PFNGLMAKETEXTUREHANDLERESIDENTARBPROC) get_fn_address("glMakeTextureHandleResidentARB");

        loaded = true;
        return true;
    }
}