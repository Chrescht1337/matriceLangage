#ifndef _SLICEMATRIX_H_
#define _SLICEMATRIX_H_
#include <cstddef>
#include <iostream>
#include "sliceOperatHandler.hpp"
#include "constSliceOperatHandler.hpp"


template<typename T,std::size_t t>
class Matrix;
template <typename R,std::size_t r>
class ShiftedIndexMatrix;

template<typename Elem,std::size_t dim>
class sliceMatrix{
    template <typename T,std::size_t t>
    friend class ShiftedIndexMatrix;
    template <typename E,std::size_t e,std::size_t p>
    friend class sliceOperatHandler;
    template <typename F,std::size_t f,std::size_t u>
    friend class constSliceOperatHandler;
    template <typename G,std::size_t g>
    friend std::ostream& operator<< (std::ostream&,const sliceMatrix<G,g>);
  private:
    ShiftedIndexMatrix<Elem,dim>& Mat;
    std::pair<std::ptrdiff_t,std::ptrdiff_t>* restrictions;
    std::size_t* steps;
    bool validRestrictions(std::initializer_list<std::pair<std::ptrdiff_t,std::ptrdiff_t>>)const;
    bool validSteps(std::initializer_list<std::size_t>)const;
    bool validAccess(std::size_t,std::ptrdiff_t)const;
    bool inStepRange(std::size_t,std::ptrdiff_t)const;
    bool validSliceToShiftedIndexMatrix()const;
  public:
    sliceMatrix(Matrix<Elem,dim>&,std::initializer_list<std::pair<std::ptrdiff_t,std::ptrdiff_t>>);
    sliceMatrix(Matrix<Elem,dim>&,std::initializer_list<std::pair<std::ptrdiff_t,std::ptrdiff_t>>,std::initializer_list<std::size_t>);
    sliceMatrix(ShiftedIndexMatrix<Elem,dim>&,std::initializer_list<std::pair<std::ptrdiff_t,std::ptrdiff_t>>);
    sliceMatrix(ShiftedIndexMatrix<Elem,dim>&,std::initializer_list<std::pair<std::ptrdiff_t,std::ptrdiff_t>>,std::initializer_list<std::size_t>);
    sliceMatrix(const sliceMatrix&);
    sliceMatrix(sliceMatrix&&);
    ~sliceMatrix();
    sliceOperatHandler<Elem,dim,dim-1> operator[](std::ptrdiff_t);
    constSliceOperatHandler<Elem,dim,dim-1> operator[](std::ptrdiff_t)const;
};
template <typename Elem>
class sliceMatrix<Elem,1>{
  private:
    ShiftedIndexMatrix<Elem,1>& Mat;
    std::size_t step;
    std::pair<std::ptrdiff_t,std::ptrdiff_t> restrictions;
    bool validRestrictions(std::pair<std::ptrdiff_t,std::ptrdiff_t>)const;
    bool validSliceToShiftedIndexMatrix()const;
  public:
    sliceMatrix(Matrix<Elem,1>&,std::pair<std::ptrdiff_t,std::ptrdiff_t>);
    sliceMatrix(Matrix<Elem,1>&,std::pair<std::ptrdiff_t,std::ptrdiff_t>,std::size_t);
    sliceMatrix(ShiftedIndexMatrix<Elem,1>&,std::pair<std::ptrdiff_t,std::ptrdiff_t>);
    sliceMatrix(ShiftedIndexMatrix<Elem,1>&,std::pair<std::ptrdiff_t,std::ptrdiff_t>,std::size_t);
    Elem& operator[](std::ptrdiff_t);
    const Elem& operator[](std::ptrdiff_t)const;
};
#endif
