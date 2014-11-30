#include "HelperMatrix.hpp"
#include <iostream>
#include <cstddef>
#include <stdexcept>

template <typename Elem,std::size_t dim>
HelperMatrix<Elem,dim>::HelperMatrix(Matrix<Elem,dim>& M)
{
    Mat=M;
}
