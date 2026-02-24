#pragma once
#include <core/types.hpp>

namespace Lux::Graphics{
    class EBO{
    public:
        const u32& id = id_;

        EBO();
        ~EBO();

        void set_size(size_t size);
        void submit_data(const void* data, size_t size, size_t offset);

    private:
        u32 id_ = 0;
        size_t size_;
        bool stored_ = false;
    };
}