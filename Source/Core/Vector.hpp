#pragma once
#include "Vector.h"
#include <Vector>

#include "Iterator.h"

namespace Hydro
{
    template<class T>
    class Vector : public Iterable<T>
    {
    public:
        Vector() : m_Vector(hydro_vector_type_create())
        {
            
        }

        Vector(const std::vector<T>& Vector)
        {
            for(const auto& element : Vector)
            {
                push(element);
            }
        }

        Vector(const T* elements, size_t count)
        {
            push(elements, count);
        }

        ~Vector() override
        {
            hydro_vector_type_free(&m_Vector);
        }

        Vector(const Vector&) = delete;
        Vector(Vector&&) = delete;
        Vector& operator=(const Vector&) = delete;
        Vector& operator=(Vector&&) = delete;

        void push(const T& element)
        {
            hydro_vector_type_push(&m_Vector, element);
        }

        void push(const T* elements, size_t count)
        {
            for(size_t i = 0; i < count; i++)
            {
                hydro_vector_type_push(&m_Vector, elements[i]);
            }
        }

        void pop() { hydro_vector_type_pop(&m_Vector); }
        size_t count() const { return m_Vector.count; }
        size_t length() const { return m_Vector.count; }
        size_t allocated() const { return m_Vector.allocated; }
        
        void reset()
        {
            hydro_vector_type_free(&m_Vector);
            m_Vector = hydro_vector_type_create();
        }

        const T* data() const { return m_Vector.data; }
        T* data() { return m_Vector.data; }

        
        Iterator<T> begin() override { return m_Vector.data; }
        Iterator<T> end() override { return m_Vector.data + m_Vector.count; }
        ConstIterator<T> begin() const override { return m_Vector.data; }
        ConstIterator<T> end() const override { return m_Vector.data + m_Vector.count; }

        bool empty() const { return hydro_vector_type_is_empty(&m_Vector); }
    private:
        HYDRO_DECLARE_TEMPLATE_VECTOR_STRUCT(T, type)
        HYDRO_IMPL_TEMPLATE_VECTOR_FUNCTIONS_STATIC(T, type)
        
        hydro_vector_type_t m_Vector;
    };
}
