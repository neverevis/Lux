#pragma once
#include <core/types.hpp>

namespace Lux::Graphics{
    class EBO{
    public:
        const u32& id = id_;

        EBO();
        ~EBO();

        void set_capacity(size_t size);
        void submit_data(const void* data, size_t size, size_t offset);

        const size_t get_capacity();

    private:
        u32 id_ = 0;
        size_t capacity_;
        bool stored_ = false;
    };
}