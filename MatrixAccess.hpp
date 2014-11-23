#ifndef _MatrixAccess_H_
#define _MatrixAccess_H_
#include <cstddef>
#include <iostream>
template <typename Elem,std::size_t dim>
class Matrix<Elem,dim>::MatrixAccess
{
	private:
		Matrix<Elem,dim>& Mat;
		std::ptrdiff_t* operatValues;
		int operatCalls;
	public:
		MatrixAccess(Matrix<Elem,dim>& mat,std::ptrdiff_t firstValue);
		MatrixAccess operator[](std::ptrdiff_t i);
}
