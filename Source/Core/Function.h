#pragma once
#include "Assertion.h"
#include "Macros.h"
#include <utility>

namespace Hydro
{
    template<typename RetType, class... Params>
    class HYDRO_API Function
    {
        using FuncPtr = RetType(*)(Params...);
    public:
        Function() = default;
        explicit Function(FuncPtr FunctionPointer) : m_FunctionPointer(FunctionPointer){}
        Function(auto FunctionPointer) : m_FunctionPointer(FunctionPointer){}
        
        bool IsBound() const { return m_FunctionPointer; }
        FuncPtr GetRawPointer() const { return m_FunctionPointer; }

        operator FuncPtr() const { return m_FunctionPointer; }
        operator FuncPtr() { return m_FunctionPointer; }
        
        
        RetType operator()(Params... params) const
        {
            return CallChecked(params...);
        }

        RetType Call(Params... params) const
        {
            return m_FunctionPointer(std::forward<Params>(params)...);
        }

        RetType CallChecked(Params... params) const
        {
            HYDRO_ASSERT(IsBound(), "Trying to call a function pointer that is not bound");
            return m_FunctionPointer(std::forward<Params>(params)...);
        }
        
        void Reset(FuncPtr FunctionPointer = nullptr)
        {
            m_FunctionPointer = FunctionPointer;
        }

    private:
        FuncPtr m_FunctionPointer = nullptr;
    };
}
