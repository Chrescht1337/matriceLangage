#include "constSliceOperatHandler.hpp"
#include "sliceMatrix.hpp"
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <memory>

template <typename Elem,std::size_t dim,std::size_t callsLeft>
constSliceOperatHandler<Elem,dim,callsLeft>::constSliceOperatHandler(const sliceMatrix<Elem,dim>& slice_,std::shared_ptr<std::ptrdiff_t>& operatValues) :slice(slice_)
{
    operatValues_.swap(operatValues);
}

template <typename Elem,std::size_t dim,std::size_t callsLeft>
constSliceOperatHandler<Elem,dim,callsLeft-1> constSliceOperatHandler<Elem,dim,callsLeft>::operator[](std::ptrdiff_t i)
{
    if (slice.validAccess(dim-callsLeft,i))
    {
        i=slice.Mat.getRealIndex(dim-callsLeft,i);
        operatValues_.get()[dim-callsLeft]=i;
        return constSliceOperatHandler<Elem,dim,callsLeft-1>(slice,operatValues_);
    }
    else
        throw std::out_of_range("Index out of range");
}

//==============================================================================
// callsLeft = 1
//==============================================================================

template <typename Elem,std::size_t dim>
constSliceOperatHandler<Elem,dim,1>::constSliceOperatHandler(const sliceMatrix<Elem,dim>& slice_,std::shared_ptr<std::ptrdiff_t>& operatValues) :slice(slice_)
{
    operatValues_.swap(operatValues);
}

template <typename Elem,std::size_t dim>
const Elem& constSliceOperatHandler<Elem,dim,1>::operator[](std::ptrdiff_t i)
{
    if (slice.validAccess(dim-1,i))
    {
        i=slice.Mat.getRealIndex(dim-1,i);
        operatValues_.get()[dim-1]=i;
        return slice.Mat.values[slice.Mat.calculateIndex(operatValues_)];
    }
    else
        throw std::out_of_range("Index out of range");
}
