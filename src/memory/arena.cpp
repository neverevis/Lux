#include <memory/arena.hpp>
#include <cstdlib>

Lux::Memory::Arena::Arena()
    : base_(nullptr)
    , offset_(0)
    , self_alloc_(false)
{}

Lux::Memory::Arena::~Arena(){
    if(self_alloc_)
        free(base_);
}

void Lux::Memory::Arena::create(size_t capacity){
    if(!base_){
        base_ = (u8*) malloc(capacity);
        capacity_ = capacity;
        self_alloc_ = true;
    }
}

void Lux::Memory::Arena::use(u8* base_address, size_t capacity){
    if(!base_){
        base_ = base_address;
        capacity_ = capacity;
        self_alloc_ = false;
    }
}

void Lux::Memory::Arena::reset(){
    offset_ = 0;
}