#pragma once
#include <graphics/data.hpp>

namespace Lux::Graphics{
    class VBO;
    class EBO;
    
    class VAO{
    public:
        VAO();
        ~VAO();

        void bind();

        void link_vbo(const VBO& vbo, size_t stride, u32 binding_index) const;
        void link_ebo(const EBO& ebo) const;

        void set_location_format(u32 location, VertexType type, u32 count, u32 offset);
        void set_location_binding(u32 location, u32 binding_index);
        void set_binding_divisor(u32 binding_index, u32 divisor);

    private:
        u32 id_;
    };
}