#pragma once
#include <core/debug.hpp>
#include <core/types.hpp>

namespace Lux::Memory{
    struct Arena{
        Arena();
        ~Arena();

        void create(size_t capacity);
        void use(u8* base_address, size_t capacity);

        template<typename T>
        T* alloc(u32 count = 1){
            /*
                Ensures that the next memory block starts at an aligned address
            */
            if(base_){
                size_t size = count * sizeof(T);
                size_t align = alignof(T);
                size_t aligned_address_offset = (offset_ + align - 1) & ~(align - 1);

                if(aligned_address_offset + size <= capacity_){
                    T* aligned_address = (T*) (base_ + aligned_address_offset);

                    offset_ = aligned_address_offset + size;
                    return aligned_address;
                }
            }

            LUX_ERROR("failed to allocate memory!");
            return nullptr;
        }

        void reset();

    private:
        u8*     base_ = nullptr;
        bool    self_alloc_;
        size_t  offset_;
        size_t  capacity_;
    };
}