#pragma once

#include <core/types.hpp>

namespace Lux::Graphics{
    class Texture{
    public:
        const u32& id;

        Texture(const char* source_path);
        ~Texture();
    private:
        u32 id_;    
    };
}