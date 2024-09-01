#pragma once
#include "Macros.h"
#include "Iterator.h"
#include <cstring>
#include <cstdint>

#define HYDRO_MALLOC(Size) ::operator new []((Size))
#define HYDRO_REALLOC(Ptr, Size) ::operator new []((Size), (Ptr))
#define HYDRO_MEMSET(Ptr, Value, Size) std::memset((Ptr), (Value), (Size))
#define HYDRO_FREE(Ptr) ::operator delete[]((Ptr))

namespace Hydro::Memory
{
    template<typename T>
    HYDRO_NODISCARD T* Malloc(size_t Count = 1)
    {
        return (T*)HYDRO_MALLOC(Count * sizeof(T));
    }
    
    template<typename T>
    HYDRO_NODISCARD T* Realloc(T* Ptr, size_t Count = 1)
    {
        return (T*)HYDRO_REALLOC(Ptr, Count * sizeof(T));
    }

    template<typename T>
    T* Memset(T* Ptr, int32_t Value, size_t Count = 1)
    {
        return (T*)HYDRO_MEMSET(Ptr, Value, Count * sizeof(T));
    }

    template<typename T>
    HYDRO_NODISCARD T* Calloc(size_t Count = 1)
    {
        T* Result = Malloc<T>(Count);
        Result = Memset(Result, 0, Count);
        return Result;
    }

    template<typename T>
    void Free(T* Ptr)
    {
        HYDRO_FREE(Ptr);
    }
}
