#ifndef _constOperatHandler_H_
#define _constOperatHandler_H_
#include <cstddef>
#include <iostream>
#include <memory>

template<typename T,std::size_t t>
class Matrix;

template<typename Elem,std::size_t dim,std::size_t callsLeft>
class constOperatHandler{
  private:
    const Matrix<Elem,dim>& M;
    std::shared_ptr<std::ptrdiff_t> operatValues_;
  public:
    constOperatHandler(const Matrix<Elem,dim>& Mat,std::shared_ptr<std::ptrdiff_t>& operatValues);
    constOperatHandler<Elem,dim,callsLeft-1> operator[](std::ptrdiff_t i);
};
template<typename Elem,std::size_t dim>
class constOperatHandler<Elem,dim,1>{
  private:
    const Matrix<Elem,dim>& M;
    std::shared_ptr<std::ptrdiff_t> operatValues_;
  public:
    constOperatHandler(const Matrix<Elem,dim>& Mat,std::shared_ptr<std::ptrdiff_t> operatValues);
    const Elem& operator[](std::ptrdiff_t i);
};
#endif
