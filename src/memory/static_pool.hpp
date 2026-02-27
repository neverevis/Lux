#pragma once
#include "core/debug.hpp"
#include <core/types.hpp>
#include <vector>

namespace Lux::Memory{
    template<typename T>
    class StaticPool{
    public:
    
        StaticPool(u32 limit)
            : limit_(limit)
            , capacity_(limit * sizeof(T))
            , occupancy_(limit,false)
            , next_index_(0)
            , free_indexes_(std::vector<u32>())
        {
            data_ = (T*) malloc(capacity_);
        }

        ~StaticPool(){
            clear();
            free(data_);
        }

        T& operator[](u32 index){
            if(is_active(index)){
                return data_[index];
            }

            LUX_VERIFY(false, "invalid index");
        }

        u32 add(){
            u32 index;

            if(free_indexes_.empty()){
                if(next_index_ < limit_){
                    index = next_index_;
                    next_index_++;
                }else{
                    LUX_ERROR("no space to store");
                    index = -1;
                }
            }else{
                index = free_indexes_.back();
                free_indexes_.pop_back();
            }

            new (&data_[index]) T();
            occupancy_[index] = true;

            return index;
        }

        void remove(u32 index){
            if(is_active(index)){
                data_[index].~T();
                occupancy_[index] = false;
                free_indexes_.push_back(index);
            }else{
                LUX_ERROR("{} is already empty", index);
            }
        }

        void clear(){
            for(int i = 0; i < limit_; i++){
                if(occupancy_[i]){
                    data_[i].~T();
                }
            }

            next_index_ = 0;
            free_indexes_.clear();
            occupancy_.assign(limit_,false);
        }

        bool is_active(u32 index){
            return occupancy_[index];
        }
    private:
        T*                  data_;

        const u32           limit_;
        std::vector<bool>   occupancy_;
        size_t              capacity_;
        u32                 next_index_;
        std::vector<u32>    free_indexes_;
    };
}