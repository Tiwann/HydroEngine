#pragma once

template<typename T>
static void Swap(T& A, T& B)
{
    T Temporary = A;
    A = B;
    B = Temporary;
}