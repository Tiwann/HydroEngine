#pragma once
#include "Memory.h"
#include "Assertion.h"

#define HYDRO_BREAK() __debugbreak()

#define HYDRO_VECTOR_CHECK(Cond) \
if(!(Cond))\
{ \
    HYDRO_BREAK(); \
}((void)0)



#define HYDRO_DECLARE_TEMPLATE_VECTOR_STRUCT(T, Name) \
typedef struct __hydro_vector_##Name \
{ \
    T* data; \
    size_t allocated; \
    size_t count; \
} hydro_vector_##Name##_t; \


#define HYDRO_IMPL_TEMPLATE_VECTOR_FUNCTIONS_STATIC(T, Name) \
static inline hydro_vector_##Name##_t hydro_vector_##Name##_create(void) \
{ \
    hydro_vector_##Name##_t vec; \
    vec.count = 0; \
    vec.allocated = 1; \
    vec.data = (T*)HYDRO_MALLOC(vec.allocated * sizeof(T)); \
    return vec;\
} \
\
static inline uint8_t hydro_vector_##Name##_push(hydro_vector_##Name##_t* vector, T element) \
{ \
    HYDRO_VECTOR_CHECK(vector); \
    HYDRO_VECTOR_CHECK(vector->data); \
    if(vector->count == vector->allocated) \
    { \
        vector->allocated *= 2; \
        T* ptr = (T*)HYDRO_REALLOC(vector->data, vector->allocated * sizeof(T)); \
        HYDRO_VECTOR_CHECK(ptr); \
        vector->data = ptr; \
    } \
    \
    vector->data[vector->count] = element; \
    vector->count++; \
    return true; \
} \
\
static inline void hydro_vector_##Name##_free(hydro_vector_##Name##_t* vector) \
{ \
    if(vector->count <= 0) return; \
    HYDRO_FREE(vector->data); \
    vector->allocated = 0; \
    vector->count = 0; \
} \
\
static inline uint8_t hydro_vector_##Name##_pop(hydro_vector_##Name##_t* vector) \
{ \
    HYDRO_VECTOR_CHECK(vector);\
    if(vector->count <= 0) return false; \
    HYDRO_MEMSET(vector->data + (vector->count - 1), 0, sizeof(T)); \
    vector->count--; \
    return true; \
}\
\
static inline uint8_t hydro_vector_##Name##_is_empty(hydro_vector_##Name##_t* vector) \
{ \
    HYDRO_VECTOR_CHECK(vector); \
    return vector->count == 0; \
}\

