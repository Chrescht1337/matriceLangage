#ifndef _SLICEMATRIX_H_
#define _SLICEMATRIX_H_
#include <cstddef>
#include <iostream>
//#include <memory>

template<typename T,std::size_t t>
class Matrix;
template <typename R,std::size_t r>
class ShiftedIndexMatrix;

template<typename Elem,std::size_t dim>
class sliceMatrix
{
    private:
        Matrix<Elem,dim>& Mat;
        std::pair<std::size_t,std::size_t>* restrictions;
        std::size_t* steps;
        bool validRestrictions(std::initializer_list<std::pair<std::size_t,std::size_t>>)const;
        bool validSteps(std::initializer_list<std::size_t>)const;
    public:
        //sliceMatrix(Matrix<Elem,dim>&);
        sliceMatrix(Matrix<Elem,dim>&,std::initializer_list<std::pair<std::size_t,std::size_t>>);
        sliceMatrix(Matrix<Elem,dim>&,std::initializer_list<std::pair<std::size_t,std::size_t>>,std::initializer_list<std::size_t>);
        ~sliceMatrix();

};
#endif
