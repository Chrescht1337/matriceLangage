#include "Matrix.hpp"
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <memory>

template <typename Elem,std::size_t dim>
Matrix<Elem,dim>::Matrix(){
	values=new Elem[dim];
	nbrOfElements=0;
	dimSizes=new std::size_t[dim];
}

template <typename Elem,std::size_t dim>
Matrix<Elem,dim>::Matrix(Elem value,std::initializer_list<std::size_t> dims){
	if (this->validDimensions(dims)){ //vérification des données
		dimSizes= new std::size_t[dim];
		int i = 0;
		//on remplit le vecteur des tailles composantes
		for (auto size : dims){
			dimSizes[i] = size;
			i++;
		}
		nbrOfElements = 1;
		//on détermine le nombre total d'éléments dans la matrice
		for (size_t j = 0; j < dim; j++){
			nbrOfElements *= this->getSizeOfDimension(j);
		}
		values = new Elem[nbrOfElements];
		//on remplit la matrice avec la valeur initiale fournie
		for (i = 0; i < nbrOfElements; i++){
			values[i] = value;
		}
	}
	else
		throw std::range_error("Number of dimensions passed not compatible with your dimension-list");
}

template <typename Elem,std::size_t dim>
Matrix<Elem,dim>::Matrix(const Matrix& Mat) : nbrOfElements(Mat.nbrOfElements){
	dimSizes=new size_t[dim];
	for (size_t i=0;i<dim;i++)
		dimSizes[i]=Mat.dimSizes[i];
	values=new Elem[nbrOfElements];
	for (size_t i=0;i<nbrOfElements;i++)
		values[i]=Mat.values[i];
}

template <typename Elem,std::size_t dim>
Matrix<Elem,dim>::Matrix(Matrix&& Mat) : dimSizes(Mat.dimSizes),nbrOfElements(Mat.nbrOfElements),values(Mat.values){
	Mat.dimSizes=nullptr;
	Mat.values=nullptr;
}

template <typename Elem,std::size_t dim>
Matrix<Elem,dim>::~Matrix(){
	delete[] dimSizes;
	delete[] values;
}

template <typename Elem,std::size_t dim>
bool Matrix<Elem,dim>::validDimensions(std::initializer_list<std::size_t> dims) const{
	// si dim est de même longueur que la liste spécifiant les composantes
	if (dim == dims.size()){
		// dim doit être strictement positif
		if (dim!=0){
			for (auto size: dims){
				//une dimension doit être stricement positive
				if (size==0)
					throw std::range_error("Invalid dimension: size <= 0 ");
			}
		}
		else //cas dim=0
			throw std::length_error("No dimensions specified");
		return true;
	}
	else
		return false;
}

template <typename Elem,std::size_t dim>
inline size_t Matrix<Elem,dim>::getSizeOfDimension(std::size_t i)const{
	if (i<dim){
		return dimSizes[i];
	}
	else
		throw std::out_of_range("Index out of range");
}

template <typename Elem,std::size_t dim>
inline size_t Matrix<Elem,dim>::getNbrOfDimensions()const{
	return dim;
}

template <typename Elem,std::size_t dim>
inline size_t Matrix<Elem,dim>::getNbrOfElements() const{
	return nbrOfElements;
}

template <typename Elem,std::size_t dim>
inline void Matrix<Elem,dim>::displayHelper(std::ostream& out,size_t i,size_t & k)const{
	out<<"[ ";
	if (i==dim-1){
		for (size_t j=0;j<this->dimSizes[i];j++){
			out<<values[k];
			k++;
			if (j<this->dimSizes[i]-1)
				out<<",";
		}
	}
	else{
		for(size_t j=0;j<this->dimSizes[i];j++){
			this->displayHelper(out,i+1,k);
		}
	}
	out<<" ]";
}


template <typename T,std::size_t t>
std::ostream& operator<< (std::ostream& out, const Matrix<T,t>& M){
	size_t k=0;
	M.displayHelper(out,0,k);
	return out;
}


template <typename Elem,std::size_t dim>
Matrix<Elem,dim>& Matrix<Elem,dim>::operator=(const Matrix& Mat){
	if (this!=&Mat){
		for (size_t i=0;i<dim;i++)
			dimSizes[i]=Mat.dimSizes[i];
		if (nbrOfElements!=Mat.nbrOfElements){
			nbrOfElements=Mat.nbrOfElements;
			delete[] values;
			values=new Elem[nbrOfElements];
		}
		for (size_t i=0;i<nbrOfElements;i++)
			values[i]=Mat.values[i];
	}
	return *this;
}

template <typename Elem,std::size_t dim>
Matrix<Elem,dim>& Matrix<Elem,dim>::operator=(Matrix&& Mat){
	if (this!=&Mat){
		delete[] dimSizes;
		dimSizes=Mat.dimSizes;
		nbrOfElements=Mat.nbrOfElements;
		delete[] values;
		values=Mat.values;
		Mat.dimSizes=nullptr;
		Mat.values=nullptr;
	}
	return *this;
}

template <typename Elem,std::size_t dim>
bool Matrix<Elem,dim>::validIndex(std::size_t dimension,std::ptrdiff_t index)const{
	return (0<=index && index<dimSizes[dimension]);
}

template <typename Elem,std::size_t dim>
std::size_t Matrix<Elem,dim>::calculateIndex(std::shared_ptr<std::ptrdiff_t> operatValues)const{
	std::size_t index=0;
	for (std::size_t i=0;i<dim-1;i++)
		index=(index +operatValues.get()[i])*this->getSizeOfDimension(i);
	index+=operatValues.get()[dim-1];
	return index;
}

template <typename Elem,std::size_t dim>
OperatHandler<Elem,dim,dim-1> Matrix<Elem,dim>::operator[](std::ptrdiff_t i){
	if (this->validIndex(0,i)){
		std::shared_ptr<std::ptrdiff_t> operatValues( new std::ptrdiff_t[dim]);
		operatValues.get()[0]=this->getRealIndex(0,i);
		return OperatHandler<Elem,dim,dim-1>(*this,operatValues);
	}
	else
		throw std::out_of_range("Index out of range");
}

template <typename Elem,std::size_t dim>
constOperatHandler<Elem,dim,dim-1> Matrix<Elem,dim>::operator[](std::ptrdiff_t i)const{
	if (validIndex(0,i)){
		std::shared_ptr<std::ptrdiff_t> operatValues( new std::ptrdiff_t[dim]);
		operatValues.get()[0]=this->getRealIndex(0,i);
		return constOperatHandler<Elem,dim,dim-1>(*this,operatValues);
	}
	else
		throw std::out_of_range("Index out of range");
}

template <typename Elem,std::size_t dim>
std::size_t Matrix<Elem,dim>::getRealIndex(std::size_t dimension,std::ptrdiff_t index)const{
//implémenté pour cette classe pour des raisons de compatibilité avec la classe
//dérivée avec des indices décalés lors de l'appel à operator[]
	return index;
}




//=============================================================================
//Matrice à 1 dimension
//=============================================================================


template <typename Elem>
Matrix<Elem,1>::Matrix(Elem value,std::size_t dims=1){
	if (dims!=0){
		dimSize=dims;
		nbrOfElements = dimSize;
		values = new Elem[nbrOfElements];
		//on remplit la matrice avec la valeur initiale fournie
		for (std::size_t i = 0; i < nbrOfElements; i++){
			values[i] = value;
		}
	}
	else
		throw std::range_error("Invalid dimension: size = 0 ");
}

template <typename Elem>
Matrix<Elem,1>::Matrix(const Matrix& Mat) : nbrOfElements(Mat.nbrOfElements),dimSize(Mat.dimSize){
	values=new Elem[nbrOfElements];
	for (size_t i=0;i<nbrOfElements;i++)
		values[i]=Mat.values[i];
}

template <typename Elem>
Matrix<Elem,1>::Matrix(Matrix&& Mat): dimSize(Mat.dimSize),nbrOfElements(Mat.nbrOfElements),values(Mat.values){}

template <typename Elem>
Matrix<Elem,1>::~Matrix(){
	delete[] values;
}

template <typename Elem>
inline size_t Matrix<Elem,1>::getSizeOfDimension()const{
	return dimSize;
}

template <typename Elem>
inline size_t Matrix<Elem,1>::getNbrOfDimensions()const{
	return 1;
}

template <typename Elem>
inline size_t Matrix<Elem,1>::getNbrOfElements() const{
	return nbrOfElements;
}

template <typename Elem>
Matrix<Elem,1>& Matrix<Elem,1>::operator=(const Matrix& Mat){
	if (this!=&Mat){
		if (nbrOfElements!=Mat.nbrOfElements){
			nbrOfElements=Mat.nbrOfElements;
			delete[] values;
			values=new Elem[nbrOfElements];
		}
		for (size_t i=0;i<nbrOfElements;i++)
			values[i]=Mat.values[i];
	}
	return *this;
}


template <typename Elem>
Matrix<Elem,1>& Matrix<Elem,1>::operator=(Matrix&& Mat){
	if (this!=&Mat){
		if (nbrOfElements!=Mat.nbrOfElements){
			nbrOfElements=Mat.nbrOfElements;
			delete[] values;
			values=new Elem[nbrOfElements];
		}
		for (size_t i=0;i<nbrOfElements;i++)
			values[i]=Mat.values[i];
		delete[] Mat.values;
	}
}

template <typename Elem>
bool Matrix<Elem,1>::validIndex(std::ptrdiff_t index)const{
	return (0<=index && index<dimSize);
}

template <typename Elem>
std::size_t Matrix<Elem,1>::getRealIndex(std::ptrdiff_t index)const{
	return index;
}

template <typename Elem>
const Elem Matrix<Elem,1>::operator[](std::ptrdiff_t i)const{
	if (this->validIndex(i)){
		i=this->getRealIndex(i);
		return values[i];
	}
	else
		throw std::out_of_range("Index out of range");
}

template <typename Elem>
Elem& Matrix<Elem,1>::operator[](std::ptrdiff_t i){
	if (this->validIndex(i)){
		i=this->getRealIndex(i);
		return values[i];
	}
	else
		throw std::out_of_range("Index out of range");
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const Matrix<T,1>& M){
	out<<"[ ";
	for (size_t i=0;i<M.dimSize;i++){
		out<<M.values[i];
		if (i<M.dimSize-1)
			out<<",";
		}
	out<<" ]";
	return out;
}
