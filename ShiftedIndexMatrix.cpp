#include "ShiftedIndexMatrix.hpp"
#include <cstddef>
#include <iostream>

template <typename Elem,std::size_t dim>
ShiftedIndexMatrix<Elem,dim>::ShiftedIndexMatrix(Elem value,std::initializer_list<std::size_t> dimensions,std::initializer_list<std::ptrdiff_t> indexShift_) : Matrix<Elem,dim>(value,dimensions)
{
    if (dim==indexShift_.size())
    {
        indexShift= new std::ptrdiff_t[dim];
        std::size_t i=0;
        for (auto shift : indexShift_)
        {
            indexShift[i]=shift;
            i++;
        }
    }
    else
        throw std::range_error("Number of index-shifts passed not compatible with your dimension-list");
}

template <typename Elem,std::size_t dim>
ShiftedIndexMatrix<Elem,dim>::ShiftedIndexMatrix(const ShiftedIndexMatrix& Mat) : Matrix<Elem,dim>(Mat),indexShift(Mat.indexShift)
{
}

template <typename Elem,std::size_t dim>
ShiftedIndexMatrix<Elem,dim>::ShiftedIndexMatrix(ShiftedIndexMatrix&& Mat) : Matrix<Elem,dim>(Mat) , indexShift(Mat.indexShift)
{
    Mat.indexShift=nullptr;
}

template <typename Elem,std::size_t dim>
ShiftedIndexMatrix<Elem,dim>::~ShiftedIndexMatrix()
{
    delete[] indexShift;
}


template <typename Elem,std::size_t dim>
bool ShiftedIndexMatrix<Elem,dim>::validIndex(std::size_t dimension,std::ptrdiff_t index)const
{
    return (indexShift[dimension]<=index && index<this->getSizeOfDimension(dimension)+indexShift[dimension]);
}

template <typename Elem,std::size_t dim>
std::size_t ShiftedIndexMatrix<Elem,dim>::getRealIndex(std::size_t dimension,std::ptrdiff_t index)const
{
    return index- indexShift[dimension];
}


template <typename Elem,std::size_t dim>
ShiftedIndexMatrix<Elem,dim>& ShiftedIndexMatrix<Elem,dim>::operator=(const ShiftedIndexMatrix& Mat)
{
    if (*this != Mat)
    {

    }
}
