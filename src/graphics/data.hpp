#pragma once

#include <core/types.hpp>

namespace Lux::Graphics{
    struct VertexData{
        f32 x,  y,  z;      //0 ~ 12
        f32 nx, ny, nz;     //12 ~ 24
        f32 u,  v;          //24 ~ 32
    };

    struct MaterialData{
        f32 r, g, b, a;     //0 ~ 16
        u64 texture_handle; //16 ~ 24
        f64 padding;        //24 ~ 32
    };

    using IndexData = u32;
    
    enum class VertexType{
        Float32,
        Int32,
        Byte,
        UnsignedByte,
        Short16
    };

}