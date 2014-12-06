#ifndef _ShiftedIndexMatrix_H_
#define _ShiftedIndexMatrix_H_
#include "Matrix.hpp"
#include <cstddef>
#include <iostream>

template <typename Elem,std::size_t dim>
class ShiftedIndexMatrix : public Matrix<Elem,dim>
{
    private:
        std::ptrdiff_t* indexShift;
        bool validIndex(std::size_t dimension,std::ptrdiff_t index)const override;
        std::size_t getRealIndex(std::size_t dimension,std::ptrdiff_t index)const override;
    public:
        ShiftedIndexMatrix(Elem,std::initializer_list<std::size_t>,std::initializer_list<std::ptrdiff_t>);
        ShiftedIndexMatrix(const ShiftedIndexMatrix& Mat);
        ShiftedIndexMatrix(ShiftedIndexMatrix&& Mat);
        ~ShiftedIndexMatrix();
        ShiftedIndexMatrix& operator=(const ShiftedIndexMatrix&);
        ShiftedIndexMatrix& operator=(ShiftedIndexMatrix&&); 

};

#endif
