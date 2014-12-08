#include "sliceMatrix.hpp"
#include "Matrix.hpp"
#include "ShiftedIndexMatrix.hpp"
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <memory>
/*
template<typename Elem,std::size_t dim,std::size_t callsLeft>
sliceMatrix<Elem,dim,callsLeft>::sliceMatrix(Matrix<Elem,dim>& Mat_):Mat(Mat)
{
    std::cout<<" const\n";
}*/

template<typename Elem,std::size_t dim>
sliceMatrix<Elem,dim>::sliceMatrix(Matrix<Elem,dim>& Mat_,std::initializer_list<std::pair<std::ptrdiff_t,std::ptrdiff_t>> restrictions_) : Mat(Mat_)
{
    if (this->validRestrictions(restrictions_))
    {
        restrictions= new std::pair<std::ptrdiff_t,std::ptrdiff_t>[dim];
        std::size_t i=0;
        for (auto vals:restrictions_)
        {
            restrictions[i]=vals;
            i++;
        }
        steps= new std::size_t[dim];
        for (std::size_t j=0;j<dim;j++)
            steps[j]=1;
    }
    else
        throw std::invalid_argument("Incompatible boundaries");
}

template<typename Elem,std::size_t dim>
sliceMatrix<Elem,dim>::sliceMatrix(Matrix<Elem,dim>& Mat_,std::initializer_list<std::pair<std::ptrdiff_t,std::ptrdiff_t>> restrictions_,std::initializer_list<std::size_t> steps_ ): Mat(Mat_)
{
    if (this->validRestrictions(restrictions_))
    {
        if (this->validSteps(steps_))
        {
            restrictions= new std::pair<std::ptrdiff_t,std::ptrdiff_t>[dim];
            std::size_t i=0;
            for (auto vals:restrictions_)
            {
                restrictions[i]=vals;
                i++;
            }
            steps= new std::size_t[dim];
            i=0;
            for (auto step : steps_)
            {
                steps[i]=step;
                ++i;
            }
        }
        else
            throw std::range_error("Incomplete step-list");
    }
    else
        throw std::invalid_argument("Incompatible boundaries");
}

template<typename Elem,std::size_t dim>
sliceMatrix<Elem,dim>::sliceMatrix(ShiftedIndexMatrix<Elem,dim>& Mat_,std::initializer_list<std::pair<std::ptrdiff_t,std::ptrdiff_t>> restrictions_) : Mat(Mat_)
{
    if (this->validRestrictions(restrictions_))
    {
        restrictions= new std::pair<std::ptrdiff_t,std::ptrdiff_t>[dim];
        std::size_t i=0;
        for (auto vals:restrictions_)
        {
            restrictions[i]=vals;
            i++;
        }
        steps= new std::size_t[dim];
        for (std::size_t j=0;j<dim;j++)
            steps[j]=1;
    }
    else
        throw std::invalid_argument("Incompatible boundaries");
}

template<typename Elem,std::size_t dim>
sliceMatrix<Elem,dim>::sliceMatrix(ShiftedIndexMatrix<Elem,dim>& Mat_,std::initializer_list<std::pair<std::ptrdiff_t,std::ptrdiff_t>> restrictions_,std::initializer_list<std::size_t> steps_ ): Mat(Mat_)
{
    if (this->validRestrictions(restrictions_))
    {
        if (this->validSteps(steps_))
        {
            restrictions= new std::pair<std::ptrdiff_t,std::ptrdiff_t>[dim];
            std::size_t i=0;
            for (auto vals:restrictions_)
            {
                restrictions[i]=vals;
                i++;
            }
            steps= new std::size_t[dim];
            i=0;
            for (auto step : steps_)
            {
                steps[i]=step;
                ++i;
            }
        }
        else
            throw std::range_error("Incomplete step-list");
    }
    else
        throw std::invalid_argument("Incompatible boundaries");
}

template<typename Elem,std::size_t dim>
sliceMatrix<Elem,dim>::sliceMatrix(const sliceMatrix& slice) : Mat(slice.Mat)
{
    restrictions = new std::pair<std::ptrdiff_t,std::ptrdiff_t>[dim];
    for (std::size_t i=0;i<dim;i++)
    {
        restrictions[i]=slice.restrictions[i];
    }
    steps=new std::size_t[dim];
    for (std::size_t i=0;i<dim;i++)
    {
        steps[i]=slice.steps[i];
    }
}

template<typename Elem,std::size_t dim>
sliceMatrix<Elem,dim>::sliceMatrix(sliceMatrix&& slice) : Mat(slice.Mat),restrictions(slice.restrictions),steps(slice.steps)
{
    slice.steps=nullptr;
    slice.restrictions=nullptr;
}

template<typename Elem,std::size_t dim>
bool sliceMatrix<Elem,dim>::validRestrictions(std::initializer_list<std::pair<std::ptrdiff_t,std::ptrdiff_t>> restrictions_)const
{
    if (restrictions_.size()==dim)
    {
        std::size_t i=0;
        for (auto vals:restrictions_)
        {
            if (vals.first <= vals.second) //sinon illogique
            {
                if (Mat.validIndex(i,vals.first))       //Seul si les deux
                    if (Mat.validIndex(i,vals.second))  //valeurs compatibles
                        i++;                            //sont acceptées
                    else
                        return false;
                else
                    return false;
            }
            else
                return false;
        }
        return true;
    }
    else
        return false;
}

template<typename Elem,std::size_t dim>
bool sliceMatrix<Elem,dim>::validSteps(std::initializer_list<std::size_t> steps)const
{
    if (steps.size()==dim)
    {
        for (auto step: steps)
        {
            if (step==0)
                throw std::invalid_argument("Invalid step: step = 0 ");
        }
        return true;
    }
    else
        return false;
}

template<typename Elem,std::size_t dim>
bool sliceMatrix<Elem,dim>::validAccess(std::size_t dimension,std::ptrdiff_t index)const
{
    return Mat.validIndex(dimension,index) && this->inStepRange(dimension,index);
}

template<typename Elem,std::size_t dim>
bool sliceMatrix<Elem,dim>::inStepRange(std::size_t dimension,std::ptrdiff_t index)const
{
    for (std::ptrdiff_t i=restrictions[dimension].first;i<=restrictions[dimension].second;i+=steps[dimension])
    {
        if (i==index)
            return true;
    }
    return false;
}

template<typename Elem,std::size_t dim>
bool sliceMatrix<Elem,dim>::validSliceToShiftedIndexMatrix()const
{
    bool answer= true;
    size_t i=0;
    while (i<dim && answer)
    {
        if (steps[i]!=1)
            answer=false;
        i++;
    }
    return answer;
}

template<typename Elem,std::size_t dim>
sliceMatrix<Elem,dim>::~sliceMatrix()
{
    delete[] steps;
    delete[] restrictions;
}

template<typename Elem,std::size_t dim>
sliceOperatHandler<Elem,dim,dim-1> sliceMatrix<Elem,dim>::operator[](std::ptrdiff_t i)
{
    if (this->validAccess(0,i))
    {
        std::shared_ptr<std::ptrdiff_t> operatValues( new std::ptrdiff_t[dim]);
        operatValues.get()[0]=Mat.getRealIndex(0,i);
        return sliceOperatHandler<Elem,dim,dim-1>(*this,operatValues);
    }
    else
        throw std::out_of_range("Invalid Index");
}

template<typename Elem,std::size_t dim>
constSliceOperatHandler<Elem,dim,dim-1> sliceMatrix<Elem,dim>::operator[](std::ptrdiff_t i)const
{
    if (this->validAccess(0,i))
    {
        std::shared_ptr<std::ptrdiff_t> operatValues( new std::ptrdiff_t[dim]);
        operatValues.get()[0]=Mat.getRealIndex(0,i);
        return sliceOperatHandler<Elem,dim,dim-1>(*this,operatValues);
    }
    else
        throw std::out_of_range("Invalid Index");
}

template<typename G,std::size_t g>
std::ostream& operator<< (std::ostream& out,const sliceMatrix<G,g> slice)
{
    out<<slice.Mat;
    return out;
}

//=============================================================================
//Matrice à 1 dimension
//=============================================================================

template<typename Elem>
sliceMatrix<Elem,1>::sliceMatrix(Matrix<Elem,1>& Mat_,std::pair<std::ptrdiff_t,std::ptrdiff_t> restrictions_) : Mat(Mat_)
{
    if (this->validRestrictions(restrictions_))
    {
        restrictions(restrictions_);
        step=1;
    }
    else
        throw std::invalid_argument("Incompatible boundaries");
}

template<typename Elem>
sliceMatrix<Elem,1>::sliceMatrix(Matrix<Elem,1>& Mat_,std::pair<std::ptrdiff_t,std::ptrdiff_t> restrictions_,std::size_t step_) : Mat(Mat_)
{
    if (this->validRestrictions(restrictions_))
    {
        restrictions=restrictions_;
        if (step_!=0)
            step=step_;
        else
            throw std::invalid_argument("Invalid step: step =0");
    }
    else
        throw std::invalid_argument("Incompatible boundaries");
}

template<typename Elem>
sliceMatrix<Elem,1>::sliceMatrix(ShiftedIndexMatrix<Elem,1>& Mat_,std::pair<std::ptrdiff_t,std::ptrdiff_t> restrictions_) : Mat(Mat_)
{
    if (this->validRestrictions(restrictions_))
    {
        restrictions=restrictions_;
        step=1;
    }
    else
        throw std::invalid_argument("Incompatible boundaries");
}

template<typename Elem>
sliceMatrix<Elem,1>::sliceMatrix(ShiftedIndexMatrix<Elem,1>& Mat_,std::pair<std::ptrdiff_t,std::ptrdiff_t> restrictions_,std::size_t step_) : Mat(Mat_)
{
    if (this->validRestrictions(restrictions_))
    {
        restrictions=restrictions_;
        if (step_!=0)
            step=step_;
        else
            throw std::invalid_argument("Invalid step: step =0");
    }
    else
        throw std::invalid_argument("Incompatible boundaries");
}

template<typename Elem>
bool sliceMatrix<Elem,1>::validRestrictions(std::pair<std::ptrdiff_t,std::ptrdiff_t> rest)const
{
    if (rest.first<=rest.second)
        if (Mat.validIndex(rest.first) && Mat.validIndex(rest.second))
            return true;
    return false;

}

template<typename Elem>
bool sliceMatrix<Elem,1>::validSliceToShiftedIndexMatrix()const
{
    return (step==1);
}

template<typename Elem>
Elem& sliceMatrix<Elem,1>::operator[](std::ptrdiff_t index)
{
    if (Mat.validIndex(index))
    {
        for (std::ptrdiff_t i=restrictions.first;i<=restrictions.second;i+=step)
        {
            if (i==index)
                return Mat[index];
        }
        throw std::out_of_range("Index blocked");
    }
    else
        throw std::out_of_range("Index out of range");
}

template<typename Elem>
const Elem& sliceMatrix<Elem,1>::operator[](std::ptrdiff_t index)const
{
    for (std::ptrdiff_t i=restrictions.first;i<=restrictions.second;i+=step)
    {
        if (i==index)
            return Mat[index];
    }
}
