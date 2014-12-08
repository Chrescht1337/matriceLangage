#ifndef _CONSTSLICEOPERATHANDLER_H_
#define _CONSTSLICEOPERATHANDLER_H_
#include <cstddef>
#include <iostream>
#include <memory>

template<typename T,std::size_t t>
class sliceMatrix;

template<typename Elem,std::size_t dim,std::size_t callsLeft>
class constSliceOperatHandler
{
    private:
        const sliceMatrix<Elem,dim>& slice;
        std::shared_ptr<std::ptrdiff_t> operatValues_;
    public:
        constSliceOperatHandler(const sliceMatrix<Elem,dim>& ,std::shared_ptr<std::ptrdiff_t>& );
        constSliceOperatHandler<Elem,dim,callsLeft-1> operator[](std::ptrdiff_t i);
};

template<typename Elem,std::size_t dim>
class constSliceOperatHandler<Elem,dim,1>
{
    private:
        const sliceMatrix<Elem,dim>& slice;
        std::shared_ptr<std::ptrdiff_t> operatValues_;

    public:
        constSliceOperatHandler(const sliceMatrix<Elem,dim>& ,std::shared_ptr<std::ptrdiff_t>& );
        const Elem& operator[](std::ptrdiff_t i);
};

#endif
