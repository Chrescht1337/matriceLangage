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
ShiftedIndexMatrix<Elem,dim>::ShiftedIndexMatrix(const ShiftedIndexMatrix& Mat) : Matrix<Elem,dim>(Mat)
{
    indexShift= new std::ptrdiff_t[this->getNbrOfElements()];
    for (std::size_t i=0;i<this->getNbrOfElements();i++)
        indexShift[i]=Mat.indexShift[i];
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
    std::ptrdiff_t bornInf=indexShift[dimension];
    std::ptrdiff_t bornSup=this->getSizeOfDimension(dimension)+indexShift[dimension];
    //return (indexShift[dimension]<=index && index<this->getSizeOfDimension(dimension)+indexShift[dimension]);
    return (bornInf<=index && index < bornSup);
}

template <typename Elem,std::size_t dim>
std::size_t ShiftedIndexMatrix<Elem,dim>::getRealIndex(std::size_t dimension,std::ptrdiff_t index)const
{
    return index-indexShift[dimension];
}


template <typename Elem,std::size_t dim>
ShiftedIndexMatrix<Elem,dim>& ShiftedIndexMatrix<Elem,dim>::operator=(const ShiftedIndexMatrix& Mat)
{
    if (this != &Mat)
    {
        Matrix<Elem,dim>::operator=(Mat);
        delete[] indexShift;
        indexShift=new std::ptrdiff_t[this->getNbrOfElements()];
        for (std::size_t i=0;i<dim;i++)
            indexShift[i]=Mat.indexShift[i];
    }
    return *this;
}

template <typename Elem,std::size_t dim>
ShiftedIndexMatrix<Elem,dim>& ShiftedIndexMatrix<Elem,dim>::operator=(ShiftedIndexMatrix&& Mat)
{
    if (this!= &Mat)
    {
        Matrix<Elem,dim>::operator=(Mat);
        delete[] indexShift;
        indexShift=Mat.indexShift;
        Mat.indexShift=nullptr;
    }
    return *this;
}

//=============================================================================
//Matrice à 1 dimension
//=============================================================================

template<typename Elem>
ShiftedIndexMatrix<Elem,1>::ShiftedIndexMatrix(Elem value,std::size_t dims,std::ptrdiff_t indexShift_=0) : Matrix<Elem,1>(value,dims)
{
    indexShift= indexShift_;
}

template<typename Elem>
ShiftedIndexMatrix<Elem,1>::ShiftedIndexMatrix(const ShiftedIndexMatrix& Mat) : Matrix<Elem,1>(Mat),indexShift(Mat.indexShift)
{
}

template<typename Elem>
ShiftedIndexMatrix<Elem,1>::ShiftedIndexMatrix(ShiftedIndexMatrix&& Mat) : Matrix<Elem,1>(Mat),indexShift(Mat.indexShift)
{
}

template<typename Elem>
bool ShiftedIndexMatrix<Elem,1>::validIndex(std::ptrdiff_t index)const
{
    std::ptrdiff_t bornSup=this->getSizeOfDimension()+indexShift;
    return indexShift<=index && index<bornSup;
}

template<typename Elem>
std::size_t ShiftedIndexMatrix<Elem,1>::getRealIndex(std::ptrdiff_t index)const
{
    return index-indexShift;
}

template<typename Elem>
ShiftedIndexMatrix<Elem,1>& ShiftedIndexMatrix<Elem,1>::operator=(const ShiftedIndexMatrix& Mat)
{
    if (this!=*Mat)
    {
        Matrix<Elem,1>::operator=(Mat);
        indexShift=Mat.indexShift;
    }
    return *this;
}

template<typename Elem>
ShiftedIndexMatrix<Elem,1>& ShiftedIndexMatrix<Elem,1>::operator=(ShiftedIndexMatrix&& Mat)
{
    if (this!=*Mat)
    {
        Matrix<Elem,1>::operator=(Mat);
        indexShift=Mat.indexShift;
    }
    return *this;
}
