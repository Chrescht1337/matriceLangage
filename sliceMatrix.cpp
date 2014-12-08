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
sliceMatrix<Elem,dim>::sliceMatrix(Matrix<Elem,dim>& Mat_,std::initializer_list<std::pair<std::size_t,std::size_t>> restrictions_) : Mat(Mat_)
{
    if (this->validRestrictions(restrictions_))
    {
        restrictions= new std::pair<std::size_t,std::size_t>[dim];
        std::size_t i=0;
        for (auto vals:restrictions_)
        {
            restrictions[i]=vals;
            i++;
        }
        steps= new std::size_t[dim];
        for (std::size_t j=0;j<dim;j++)
            steps[j]=0;
    }
    else
        throw std::invalid_argument("Incompatible boundaries");
}

template<typename Elem,std::size_t dim>
sliceMatrix<Elem,dim>::sliceMatrix(Matrix<Elem,dim>& Mat_,std::initializer_list<std::pair<std::size_t,std::size_t>> restrictions_,std::initializer_list<std::size_t> steps_ ): Mat(Mat_)
{
    if (this->validRestrictions(restrictions_))
    {
        if (this->validSteps(steps_))
        {
            restrictions= new std::pair<std::size_t,std::size_t>[dim];
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
            }
        }
        else
            throw std::range_error("Incomplete step-list");
    }
    else
        throw std::invalid_argument("Incompatible boundaries");
}


template<typename Elem,std::size_t dim>
bool sliceMatrix<Elem,dim>::validRestrictions(std::initializer_list<std::pair<std::size_t,std::size_t>> restrictions_)const
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
                throw std::range_error("Invalid dimension: size <= 0 ");
        }
        return true;
    }
    else
        return false;
}

template<typename Elem,std::size_t dim>
sliceMatrix<Elem,dim>::~sliceMatrix()
{
    delete[] steps;
    delete[] restrictions;
}
