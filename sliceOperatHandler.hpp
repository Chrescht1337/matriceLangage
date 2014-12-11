#ifndef _SLICEOPERATHANDLER_H_
#define _SLICEOPERATHANDLER_H_
#include <cstddef>
#include <iostream>
#include <memory>

template<typename T,std::size_t t>
class sliceMatrix;

template<typename Elem,std::size_t dim,std::size_t callsLeft>
class sliceOperatHandler{
  private:
    sliceMatrix<Elem,dim>& slice;
    std::shared_ptr<std::ptrdiff_t> operatValues_;
  public:
    sliceOperatHandler(sliceMatrix<Elem,dim>& ,std::shared_ptr<std::ptrdiff_t>& );
    sliceOperatHandler<Elem,dim,callsLeft-1> operator[](std::ptrdiff_t i);
};

template<typename Elem,std::size_t dim>
class sliceOperatHandler<Elem,dim,1>{
  private:
    sliceMatrix<Elem,dim>& slice;
    std::shared_ptr<std::ptrdiff_t> operatValues_;
  public:
    sliceOperatHandler(sliceMatrix<Elem,dim>& ,std::shared_ptr<std::ptrdiff_t>& );
    Elem& operator[](std::ptrdiff_t i);
};
#endif
