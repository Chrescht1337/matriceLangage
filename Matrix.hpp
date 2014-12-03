#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <cstddef>
#include <iostream>
#include "OperatHandler.hpp"

template <typename Elem,std::size_t dim>
class Matrix
{
    private:
        Elem * values;
        std::size_t nbrOfElements;
        std::size_t* dimSizes;

        template <typename T,std::size_t t>
        friend std::ostream& operator<< (std::ostream&, const Matrix<T,t>&);
        inline void displayHelper(std::ostream& out, size_t i,size_t & t)const;
        bool validDimensions(std::initializer_list<std::size_t> dims)const;
        bool validIndex(std::size_t dimension,std::ptrdiff_t index)const;
        std::size_t getRealIndex(std::size_t dimension,std::ptrdiff_t index)const;
        std::size_t calculateIndex(std::ptrdiff_t* )const;
        //const Elem& at(std::size_t t)const{return values[t];}
        template <typename S,std::size_t s,std::size_t j>
        friend class OperatHandler;
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
        OperatHandler<Elem,dim,dim-1> operator[](std::ptrdiff_t i);
        OperatHandler<Elem,dim,dim-1> operator[](std::ptrdiff_t i)const;
};
template<typename Elem>
class Matrix<Elem,1>
{
private:
        Elem * values;
        std::size_t nbrOfElements;
        std::size_t* dimSizes;
        //std::size_t dimensions;

        template <typename T>
        friend std::ostream& operator<< (std::ostream&, const Matrix<T,1>&);
        bool validDimensions(std::initializer_list<std::size_t> dims)const;
        bool validIndex(std::ptrdiff_t index)const;
        //std::size_t calculateIndex(std::ptrdiff_t* operatValues)const;

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
        Elem& operator[](std::ptrdiff_t i);
        const Elem operator[](std::ptrdiff_t i)const;

};
/*
template <typename Elem,std::size_t dim,int t>
class Matrix<Elem,dim>::ok<t>
{
private:
    int i;
public:
    ok(int a){i=t;std::cout<<"ok "<<i<<" "<<a;};

};*/
#endif
