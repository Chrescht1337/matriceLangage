#include "constOperatHandler.hpp"
#include "Matrix.hpp"
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <memory>

template <typename Elem,std::size_t dim,std::size_t callsLeft>
constOperatHandler<Elem,dim,callsLeft>::constOperatHandler(const Matrix<Elem,dim>& Mat,std::shared_ptr<std::ptrdiff_t>& operatValues) :M(Mat){
  operatValues_.swap(operatValues);
}

template <typename Elem,std::size_t dim,std::size_t callsLeft>
constOperatHandler<Elem,dim,callsLeft-1> constOperatHandler<Elem,dim,callsLeft>::operator[](std::ptrdiff_t i){
  if (M.validIndex(dim-callsLeft,i)){
    i=M.getRealIndex(dim-callsLeft,i);
    operatValues_.get()[dim-callsLeft]=i;
    return constOperatHandler<Elem,dim,callsLeft-1>(M,operatValues_);
  }
  else
    throw std::out_of_range("Index out of range");
}

//==============================================================================
// callsLeft = 1
//==============================================================================

template <typename Elem,std::size_t dim>
constOperatHandler<Elem,dim,1>::constOperatHandler(const Matrix<Elem,dim>& Mat,std::shared_ptr<std::ptrdiff_t> operatValues) :M(Mat){
  operatValues_.swap(operatValues);
}

template <typename Elem,std::size_t dim>
const Elem& constOperatHandler<Elem,dim,1>::operator[](std::ptrdiff_t i){
  if (M.validIndex(dim-1,i)){
    i=M.getRealIndex(dim-1,i);
    operatValues_.get()[dim-1]=i;
    return M.values[M.calculateIndex(operatValues_)];
  }
  else
    throw std::out_of_range("Index out of range");
}
