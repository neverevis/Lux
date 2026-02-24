#pragma once

#include <graphics/vbo.hpp>
#include <graphics/ebo.hpp>
#include <graphics/data.hpp>
#include <core/types.hpp>


namespace Lux::Graphics{
    struct Mesh{
    public:
        void set_vertices_capacity(size_t size);
        void set_indices_capacity(size_t size);
        void set_vertices(VertexData* vertices, u32 count);
        void set_indices(IndexData* indices, u32 count);

        const VBO& get_vbo();
        const EBO& get_ebo();
        u32 get_index_count();
    private:
        VBO vertices_vbo_;
        EBO indices_ebo_;

        size_t vertices_vbo_size_ = 0;
        size_t indices_ebo_size_ = 0;

        u32 index_count_ = 0;
    };
}