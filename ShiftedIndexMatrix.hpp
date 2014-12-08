#ifndef _ShiftedIndexMatrix_H_
#define _ShiftedIndexMatrix_H_
#include "Matrix.hpp"
#include "sliceMatrix.hpp"
#include <cstddef>
#include <iostream>

template <typename Elem,std::size_t dim>
class ShiftedIndexMatrix : public Matrix<Elem,dim>
{
        template <typename D,std::size_t d>
        friend class sliceMatrix;
        template <typename T,std::size_t t,std::size_t g>
        friend class sliceOperatHandler;
    private:
        std::ptrdiff_t* indexShift;
        bool validIndex(std::size_t dimension,std::ptrdiff_t index)const override;
        std::size_t getRealIndex(std::size_t dimension,std::ptrdiff_t index)const override;
    public:
        ShiftedIndexMatrix(Elem,std::initializer_list<std::size_t>,std::initializer_list<std::ptrdiff_t>);
        ShiftedIndexMatrix(const ShiftedIndexMatrix& Mat);
        ShiftedIndexMatrix(ShiftedIndexMatrix&& Mat);
        ShiftedIndexMatrix(const Matrix<Elem,dim>& Mat);
        ShiftedIndexMatrix(Matrix<Elem,dim>&& Mat);
        ShiftedIndexMatrix(const sliceMatrix<Elem,dim>& );
        ShiftedIndexMatrix(sliceMatrix<Elem,dim>&& );
        ~ShiftedIndexMatrix();
        ShiftedIndexMatrix& operator=(const ShiftedIndexMatrix&);
        ShiftedIndexMatrix& operator=(ShiftedIndexMatrix&&);
        ShiftedIndexMatrix& operator=(const sliceMatrix<Elem,dim>&);
        ShiftedIndexMatrix& operator=(sliceMatrix<Elem,dim>&&);
};
template <typename Elem>
class ShiftedIndexMatrix<Elem,1> : public Matrix<Elem,1>
{
        template <typename Z,std::size_t z>
        friend class sliceMatrix;
    private:
        std::ptrdiff_t indexShift;
        bool validIndex(std::ptrdiff_t index)const override;
        std::size_t getRealIndex(std::ptrdiff_t index)const override;
    public:
        ShiftedIndexMatrix(Elem,std::size_t,std::ptrdiff_t);
        ShiftedIndexMatrix(const ShiftedIndexMatrix& Mat);
        ShiftedIndexMatrix(ShiftedIndexMatrix&& Mat);
        ShiftedIndexMatrix(const Matrix<Elem,1>& Mat_);
        ShiftedIndexMatrix(Matrix<Elem,1>&& Mat_);
        ShiftedIndexMatrix(const sliceMatrix<Elem,1>& sliceMat);
        ShiftedIndexMatrix(sliceMatrix<Elem,1>&& sliceMat);
        //~ShiftedIndexMatrix();
        ShiftedIndexMatrix& operator=(const ShiftedIndexMatrix&);
        ShiftedIndexMatrix& operator=(ShiftedIndexMatrix&&);
        ShiftedIndexMatrix& operator=(const sliceMatrix<Elem,1>&);
        ShiftedIndexMatrix& operator=(sliceMatrix<Elem,1>&&);
};
#endif
