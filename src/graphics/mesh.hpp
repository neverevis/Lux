#pragma once

#include <graphics/vbo.hpp>
#include <graphics/ebo.hpp>
#include <graphics/data.hpp>
#include <vector>
#include <core/types.hpp>


namespace Lux::Graphics{
    struct Mesh{
    public:
        Mesh();
        ~Mesh();
        const i32 id;

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
        u32 index_count_ = 0;

        static i32 assign_id();

        static i32 next_id;
        static std::vector<i32> free_index_list;
    };
}