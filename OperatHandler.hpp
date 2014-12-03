#ifndef _OperatHandler_H_
#define _OperatHandler_H_
#include <cstddef>
#include <iostream>
//#include "Matrix.hpp" forward declaration so no include

template<typename T,std::size_t t>
class Matrix;

template<typename Elem,std::size_t dim,std::size_t callsLeft>
class OperatHandler
{
    private:
        Matrix<Elem,dim>& M;
        std::ptrdiff_t* operatValues_;

    public:
        OperatHandler(Matrix<Elem,dim>& Mat,std::ptrdiff_t* operatValues);
        OperatHandler<Elem,dim,callsLeft-1> operator[](std::ptrdiff_t i);
        ~OperatHandler();

};
template<typename Elem,std::size_t dim>
class OperatHandler<Elem,dim,1>
{
    private:
        Matrix<Elem,dim>& M;
        std::ptrdiff_t* operatValues_;

    public:
        OperatHandler(Matrix<Elem,dim>& Mat,std::ptrdiff_t* operatValues);
        Elem& operator[](std::ptrdiff_t i);
        const Elem& operator[](std::ptrdiff_t i)const;
        ~OperatHandler();
};


#endif
