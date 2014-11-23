#include "MatrixAccess.hpp"
#include <iostream>
#include <cstddef>
#include <stdexcept>


template <typename Elem,std::size_t dim>
Matrix<Elem,dim>::MatrixAccess::MatrixAccess(Matrix<Elem,dim>& mat,std::ptrdiff_t firstValue)
{
	operatCalls=1;
	Mat=mat;
	operatValues= new ptrdiff_t[Mat.getNbrOfDimensions()];
	operatValues[0]=firstValue;
}


template <typename Elem,std::size_t dim>
MatrixAccess Matrix<Elem,dim>::MatrixAccess::operator[](std::ptrdiff_t i)
{
	if (operatCalls<Mat.getNbrOfDimensions())
	{
		if (0<=i && i<Mat.getSizeOfDimension(operatCalls))
		{
			operatValues[operatCalls]=i;
			operatCalls+=1;
			return (*this);
		}
		else
			throw std::out_of_range("Index out of range");
	}
	//else//typeError Elem not subscriptable
//		throw std::
}
