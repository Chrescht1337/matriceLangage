#ifndef _HelperMatrix_H_
#define _HelperMatrix_H_
#include <cstddef>
#include <iostream>
template<typename T,std::size_t t>
class Matrix;
template<typename Elem,std::size_t dim>
class HelperMatrix
{
    private:
        Matrix<Elem,dim>& Mat;
        std::ptrdiff_t* operatValues;
        std::size_t operatCalls;
    public:
        HelperMatrix(Matrix<Elem,dim>& M);

};
template<typename Elem>
class HelperMatrix<Elem,1>
{

};


#endif
