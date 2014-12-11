#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <cstddef>
#include <iostream>
#include <memory>
#include "OperatHandler.hpp"
#include "constOperatHandler.hpp"
#include "sliceMatrix.hpp"

template <typename Elem,std::size_t dim>
class Matrix{
    template <typename T,std::size_t t>
    friend std::ostream& operator<< (std::ostream&, const Matrix<T,t>&);
    template <typename S,std::size_t s,std::size_t j>
    friend class OperatHandler;
    template <typename F,std::size_t f,std::size_t h>
    friend class constOperatHandler;
    template <typename D,std::size_t d>
    friend class sliceMatrix;
    template <typename A,std::size_t a,std::size_t b>
    friend class sliceOperatHandler;

  private:
    inline void displayHelper(std::ostream& out, size_t i,size_t & t)const;
    Elem * values;
    std::size_t nbrOfElements;
    std::size_t* dimSizes;

    bool validDimensions(std::initializer_list<std::size_t> dims)const;
    virtual bool validIndex(std::size_t dimension,std::ptrdiff_t index)const;
    virtual std::size_t getRealIndex(std::size_t dimension,std::ptrdiff_t index)const;
    std::size_t calculateIndex(std::shared_ptr<std::ptrdiff_t> operatValues)const;
  public:
    Matrix(Elem value,std::initializer_list<std::size_t> dims);
    Matrix(const Matrix& Mat);
    Matrix(Matrix&& Mat);
    Matrix();
    ~Matrix();
    inline size_t getSizeOfDimension(std::size_t i)const;
    inline size_t getNbrOfDimensions() const;
    inline size_t getNbrOfElements() const;
    Matrix& operator=(const Matrix& Mat);
    Matrix& operator=(Matrix&& Mat);
    OperatHandler<Elem,dim,dim-1> operator[](std::ptrdiff_t i);
    constOperatHandler<Elem,dim,dim-1> operator[](std::ptrdiff_t i)const;
};

template<typename Elem>
class Matrix<Elem,1>{
    template <typename T>
    friend std::ostream& operator<< (std::ostream&, const Matrix<T,1>&);
    template <typename Z,std::size_t z>
    friend class sliceMatrix;
  private:
    Elem * values;
    std::size_t nbrOfElements;
    std::size_t dimSize;

    virtual bool validIndex(std::ptrdiff_t index)const;
    virtual std::size_t getRealIndex(std::ptrdiff_t index)const;
  public:
    Matrix(Elem value,std::size_t dims);
    Matrix(const Matrix& Mat);
    Matrix(Matrix&& Mat);
    ~Matrix();
    inline size_t getSizeOfDimension()const;
    inline size_t getNbrOfDimensions() const;
    inline size_t getNbrOfElements() const;
    Matrix& operator=(const Matrix& Mat);
    Matrix& operator=(Matrix&& Mat);
    Elem& operator[](std::ptrdiff_t i);
    const Elem operator[](std::ptrdiff_t i)const;
};
#endif
