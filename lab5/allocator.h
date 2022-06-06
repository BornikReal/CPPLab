#include "Chunk.h"

#pragma once
namespace bornik {
    template<typename T, size_t num_of_chunks, size_t chunks_size>
    class allocator {
    public:
        typedef size_t size_type;
        [[maybe_unused]] typedef ptrdiff_t difference_type;
        typedef T *pointer;
        [[maybe_unused]] typedef const T *const_pointer;
        [[maybe_unused]] typedef T &reference;
        [[maybe_unused]] typedef const T &const_reference;
        typedef T value_type;
        size_type num_of_chunks_ = num_of_chunks;
        size_type chunk_size_ = chunks_size;
        pointer start_;
        pointer end_;

        template<typename U>
        struct rebind {
            typedef allocator<U, num_of_chunks, chunks_size> other;
        };

        explicit allocator() {
            start_ = static_cast<pointer>(malloc((chunk_size_ * sizeof(value_type) + 8) * num_of_chunks_ + 16));
            end_ = start_ + (chunk_size_ * sizeof(value_type) + 8) * num_of_chunks_ + 16;
            auto *chunk = reinterpret_cast<long long *>(start_);
            *chunk = reinterpret_cast<long long>(reinterpret_cast<long long *>(start_) + 2);
            *(chunk + 1) = 1;
            auto cur = reinterpret_cast<pointer>(chunk + 2);
            for (int i = 0; i < num_of_chunks_; ++i) {
                Chunk <value_type> new_chunk(cur, chunk_size_);
                cur = new_chunk.next();
            }
            *(reinterpret_cast<long long *>(cur - chunk_size_) - 1) = LLONG_MAX;
            Chunk <value_type> cur_chunk(reinterpret_cast<pointer>(*reinterpret_cast<long long *>(start_)));
        }

        allocator(const allocator &alloc) {
            if (alloc == *this)
                return;
            auto *chunk = static_cast<long long *>(alloc.start_) + 1;
            *chunk += 1;
            start_ = alloc.start_;
            end_ = alloc.end_;
            chunk_size_ = alloc.chunk_size_;
        }

        template<typename Tp, size_t num_of_chunks2 = 1000, size_t chunks_size2 = 1000>
        explicit allocator(const allocator<Tp, num_of_chunks2, chunks_size2> &alloc) {
            auto *chunk = reinterpret_cast<long long *>(alloc.start_) + 1;
            *chunk += 1;
            start_ = reinterpret_cast<T *>(alloc.start_);
            end_ = reinterpret_cast<T *>(alloc.end_);
            chunk_size_ = alloc.chunk_size_ * float(sizeof(T)) / sizeof(Tp);
        }

        allocator &operator=(const allocator &rhs) {
            if (rhs == *this)
                return *this;
            auto *chunk = static_cast<long long *>(start_) + 1;
            *chunk += 1;
            chunk_size_ = rhs.chunk_size_;
        }

        bool operator==(const allocator &rhs) {
            return start_ == rhs.start_;
        }

        bool operator!=(const allocator &rhs) {
            return start_ != rhs.start_;
        }

        pointer allocate(size_type size = 1) {
            if (size > chunk_size_)
                throw std::bad_alloc();
            T *chunk = reinterpret_cast<pointer>(*reinterpret_cast<long long *>(start_));
            if (chunk - end_ > 0)
                throw std::bad_alloc();
            Chunk <value_type> cur_chunk(chunk);
            *reinterpret_cast<long long *>(start_) = reinterpret_cast<long long>(cur_chunk.next());
            return cur_chunk.mem();
        }

        void deallocate(pointer pos, size_type size) {
            long long *header = reinterpret_cast<long long *>(pos) - 1;
            *header = static_cast<long long>(*reinterpret_cast<long long *>(start_));
            *reinterpret_cast<long long *>(start_) = reinterpret_cast<long long>(header);
        }

        size_type max_size() {
            return chunk_size_;
        }

        ~allocator() {
            long long *chunk = reinterpret_cast<long long *>(start_) + 1;
            if (*chunk == 1)
                free(start_);
            else
                *chunk -= 1;
        }
    };
};