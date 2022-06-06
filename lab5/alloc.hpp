#include <iostream>
#include <fstream>
#include <exception>
#include <memory>
template <typename T>
struct Chunk {
public:
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;

    Chunk *next;
    pointer p;

    Chunk(pointer p_ = nullptr, Chunk* next_ = nullptr):
            p(p_), next(next_) {}

    Chunk(const Chunk&) = default;

    ~Chunk() {
        if (next != nullptr)
            delete next;
    }

    static bool isPrint;
    void print(std::string s = "") {
        std::ofstream fout("chunk.log", isPrint ? std::ios::app : std::ios::out);
        isPrint = true;
        fout << "\n" << s << "\n" << "Chunks:\n";
        Chunk *cur = this;
        int k = 8;
        while (cur != nullptr) {
            fout << cur->p << " -> ";
            if (k % 5 == 0)
                fout << "\n";
            k++;
            cur = cur->next;
        }
        fout << "\nend Chunk\n";
    }
};

template <typename T>
bool Chunk<T>::isPrint = false;

template <typename T>
void freeChunks(Chunk<T> *chunks) {
    if (chunks->next != nullptr)
        freeChunks(chunks->next);
    free(chunks);
}


template<typename T>
class MyAllocator {
public:
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;

    template <typename U>
    struct rebind {
        typedef MyAllocator<U> other;
    };

    pointer buffer;
    size_type count, size; //размер участка и макс. количество переменных в участке
    Chunk<value_type> **chunks; //просто указатель на указатель на участок
    bool destroy, contCopy;

    MyAllocator(size_type size_ = 512, size_type count_ = 10000):
            count(count_), size(size_), destroy(true), contCopy(false),
            buffer(static_cast<pointer>(malloc(count_ * size_ * sizeof(value_type))))
    {
        if (!buffer)
            throw std::invalid_argument("A?");//std::bad_alloc();
        chunks = new Chunk<value_type>*();
        *chunks = new Chunk<value_type>(buffer);
        pointer end = buffer + count * size;
        Chunk<value_type> *cur = *chunks;
        for (pointer pi = buffer + size; pi < end; pi += size) {
            cur->next = new Chunk<value_type>(pi);
            cur = cur->next;
        }
        //(*chunks)->print("default");
        std::cout << "default constructor " << buffer << " " <<  buffer + count * size << std::endl;
    }

    template<typename U>
    MyAllocator (const MyAllocator<U>& alloc):
            buffer(reinterpret_cast<pointer>(alloc.buffer)),
            size(alloc.size * sizeof(U) / sizeof(T)),
            count(alloc.count), destroy(alloc.contCopy ? true : false), contCopy(false),
            chunks(reinterpret_cast<Chunk<value_type>**>(alloc.chunks))
    {
        std::cout << "\ndifferent copy construct ";
        std::cout << chunks << ' ' << alloc.chunks << "\n\n";
    }


    MyAllocator (const MyAllocator &alloc):
            buffer(alloc.buffer),
            size(alloc.size),
            count(alloc.count), destroy(alloc.contCopy ? true : false), contCopy(false),
            chunks(alloc.chunks)
    {
        std::cout << "\n same copy construct ";
        std::cout << chunks << ' ' << alloc.chunks << "\n\n";
    }

    bool operator==(const MyAllocator &alloc) const noexcept{
        return buffer == alloc.buffer;
    }
    bool operator!=(const MyAllocator &alloc) const noexcept{
        return buffer != alloc.buffer;
    }

    static MyAllocator select_on_container_copy_construction(){
        MyAllocator helper;
        helper.destroy = false;
        helper.contCopy = true;
        //std::cout << "select_on_container_copy_construction " << helper.buffer <<"\n";
        return helper;
    }

    pointer allocate(size_type n) {
        std::cout << n << " < " << size << " is n > size: " << (n > size) << " - allocate " << std::endl;
        if (n > size) {
            using namespace std::string_literals;
            std::cout << "WTF??";
            throw std::bad_alloc();
            //throw std::invalid_argument(std::to_string(n) + " is bigger than size of chunk "s + std::to_string(size));
        }
        if (chunks == nullptr || *chunks == nullptr) {
            throw std::invalid_argument("B?");//std::bad_alloc();
        }
        pointer res = (*chunks)->p;
        *chunks = (*chunks)->next;
        //(*chunks)->print();
        //std::cout << res << std::endl;
        return res;
    }

    void deallocate(pointer p, size_type) {
        if (p == nullptr)
            return;
        //std::cout << p << ' '<< " deallocate\n";
        *chunks = new Chunk<value_type>(p, (*chunks));
        //(*chunks)->print("deallocate");
    }

    ~MyAllocator() {
        if (destroy && buffer != nullptr && !contCopy) {
            std::cout << "destructor: " << buffer << "\n";
            free(buffer);
            freeChunks(*chunks);
        }
    }

};