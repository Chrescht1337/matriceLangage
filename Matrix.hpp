#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <cstddef>
#include <iostream>

template <typename Elem,std::size_t dim>
class Matrix
{
    private:
        Elem * values;
        std::size_t nbrOfElements;
        std::size_t* dimSizes;
        std::size_t dimensions;
        bool validDimensions(std::initializer_list<std::size_t> dims)const;
        bool validIndex(std::size_t dimension,std::ptrdiff_t index)const;
        std::size_t calculateIndex(std::ptrdiff_t* operatValues)const;
        inline const Elem at(std::size_t i)const;
        inline Elem& at(std::size_t i);
        class MatrixAccess;
    public:
        Matrix(Elem value,std::initializer_list<std::size_t> dims);
        Matrix(const Matrix& Mat);
        Matrix(Matrix&& Mat);
        ~Matrix();
        inline size_t getSizeOfDimension(std::size_t i)const;
        inline size_t getNbrOfDimensions() const;
        inline size_t getNbrOfElements() const;
        Matrix& operator=(const Matrix& Mat);
        Matrix& operator=(Matrix&& Mat);
        Matrix<Elem,dim>::MatrixAccess operator[](std::ptrdiff_t i);

};

#endif
