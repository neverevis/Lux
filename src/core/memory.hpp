#pragma once
#include <core/debug.hpp>
#include <core/types.hpp>

namespace Lux::Core{
    struct Arena{
        u8*     base;

        Arena(size_t capacity);
        ~Arena();

        template<typename T>
        T* alloc(u32 count = 1){
            /*
                Ensures that the next memory block starts at an aligned address
            */
            size_t size = count * sizeof(T);
            size_t align = alignof(T);
            size_t aligned_address_offset = (offset_ + align - 1) & ~(align - 1);

            if(aligned_address_offset + size <= capacity_){
                T* aligned_address = base + aligned_address_offset;

                offset_ = aligned_address_offset + size;
                return aligned_address;
            }

            LUX_ERROR("failed to allocate memory!");
            return nullptr;
        }

        void reset();

    private:
        size_t  offset_;
        size_t  capacity_;
    };
}