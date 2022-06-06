#include <iostream>

#pragma once

template<typename T>
class Chunk {
private:
    long long *start_;
public:
    explicit Chunk(void *start) : start_(static_cast<long long *>(start)) {}

    Chunk(void *start, size_t num) : start_(static_cast<long long *>(start)) {
        *start_ = reinterpret_cast<long long>(static_cast<T *>(start) + num) + 8;
    }

    T *next() {
        return reinterpret_cast<T *>(*start_);
    }

    T *mem() {
        return reinterpret_cast<T *>(start_ + 1);
    }
};