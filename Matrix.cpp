#include "Matrix.hpp"
#include <iostream>
#include <cstddef>
#include <stdexcept>



template <typename Elem,std::size_t dim>
Matrix<Elem,dim>::Matrix(Elem value,std::initializer_list<std::size_t> dims)
{
	if (validDimensions(dims)) //vérification des données
	{
		dimensions=dim;
		dimSizes= new std::size_t[dimensions];
		int i = 0;
		for (auto size : dims) //on remplit le vecteur des tailles composantes
		{
			dimSizes[i] = size;
			i++;
		}
		nbrOfElements = 1;
		for (size_t j = 0; j < dim; j++)
		//on détermine le nombre total d'éléments dans la matrice
		{
			nbrOfElements *= getSizeOfDimension(j);
		}
		values = new Elem[nbrOfElements];
		for (i = 0; i < nbrOfElements; i++)
		//on remplit la matrice avec la valeur initiale fournie
		{
			values[i] = value;
		}
	}
	else
		throw std::range_error("Number of dimensions passed not compatible with your dimension-list");
}

template <typename Elem,std::size_t dim>
Matrix<Elem,dim>::Matrix(const Matrix& Mat)
{
	dimensions=Mat.getNbrOfDimensions();
	dimSizes=new size_t[dimensions];
	for (size_t i=0;i<dimensions;i++)
		dimSizes[i]=Mat.getSizeOfDimension(i);
	nbrOfElements=Mat.getNbrOfElements();
	values=new Elem[nbrOfElements];
	for (size_t i=0;i<nbrOfElements;i++)
		values[i]=Mat.at(i);
}

template <typename Elem,std::size_t dim>
Matrix<Elem,dim>::Matrix(Matrix&& Mat)
{
	dimensions=Mat.dimensions;
	dimSizes=Mat.dimSizes;
	Mat.dimSizes=nullptr;
	nbrOfElements=Mat.nbrOfElements;
	values = Mat.values;
	Mat.values=nullptr;
}

template <typename Elem,std::size_t dim>
Matrix<Elem,dim>::~Matrix()
{
	delete[] dimSizes;
	delete[] values;
}

template <typename Elem,std::size_t dim>
inline const Elem Matrix<Elem,dim>::at(std::size_t i)const
{
	return values[i];
}

template <typename Elem,std::size_t dim>
inline Elem& Matrix<Elem,dim>::at(std::size_t i)
{
	return values[i];
}

template <typename Elem,std::size_t dim>
bool Matrix<Elem,dim>::validDimensions(std::initializer_list<std::size_t> dims) const
{
	if (dim == dims.size())
	// si dim est de même longueur que la liste spécifiant les composantes
	{
		if (dims.size()!=0)// liste non vide
		{
			for (auto size: dims)
			{
				if (size<=0)	//une dimension doit être stricement positive
					throw std::range_error("Invalid dimension: size <= 0 ");
			}
		}
		else //cas si liste est vide
			throw std::length_error("No dimensions specified");
		return true;
	}
	else return false;
}

template <typename Elem,std::size_t dim>
inline size_t Matrix<Elem,dim>::getSizeOfDimension(std::size_t i)const
{
	if (i<dimensions)
	{
		return dimSizes[i];
	}
	else
		throw std::out_of_range("Index out of range");
}

template <typename Elem,std::size_t dim>
inline size_t Matrix<Elem,dim>::getNbrOfDimensions()const
{
	return dimensions;
}

template <typename Elem,std::size_t dim>
inline size_t Matrix<Elem,dim>::getNbrOfElements() const
{
	return nbrOfElements;
}

template <typename Elem,std::size_t dim>
inline void Matrix<Elem,dim>::displayHelper(std::ostream& out,size_t i,size_t & k)const
{
	out<<"[ ";
	if (i==getNbrOfDimensions()-1)
	{
		for (size_t j=0;j<getSizeOfDimension(i);j++)
		{
			//std::cout<<"d "<<k;
			out<<at(k);
			k++;
		}
	}
	else
	{
		for(size_t j=0;j<getSizeOfDimension(i);j++)
		{
			//std::cout<<"g "<<k;
			displayHelper(out,i+1,k);
		}
	}
	out<<" ]";
}


template <typename T,std::size_t t>
std::ostream& operator<< (std::ostream& out, const Matrix<T,t>& M)
{
	size_t k=0;
	M.displayHelper(out,0,k);
	return out;
}


template <typename Elem,std::size_t dim>
Matrix<Elem,dim>& Matrix<Elem,dim>::operator=(const Matrix& Mat)
{
	if (this!=&Mat)
	{
		if (dimensions!=Mat.getNbrOfDimensions())
		{
			dimensions =Mat.getNbrOfDimensions();
			delete [] dimSizes;
			dimSizes=new size_t[dimensions];
		}
		for (size_t i=0;i<dimensions;i++)
			dimSizes[i]=Mat.getSizeOfDimension(i);
		if (nbrOfElements!=Mat.getNbrOfElements())
		{
			nbrOfElements=Mat.getNbrOfElements();
			delete[] values;
			values=new Elem[nbrOfElements];
		}
		for (size_t i=0;i<nbrOfElements;i++)
			values[i]=Mat.at(i);
	}
	return *this;
}

template <typename Elem,std::size_t dim>
Matrix<Elem,dim>& Matrix<Elem,dim>::operator=(Matrix&& Mat)
{
	if (this!=&Mat)
	{
		if (dimensions!=Mat.getNbrOfDimensions())
		{
			dimensions =Mat.getNbrOfDimensions();
			delete [] dimSizes;
			dimSizes=new size_t[dimensions];
		}
		for (size_t i=0;i<dimensions;i++)
			dimSizes[i]=Mat.getSizeOfDimension(i);
		if (nbrOfElements!=Mat.getNbrOfElements())
		{
			nbrOfElements=Mat.getNbrOfElements();
			delete[] values;
			values=new Elem[nbrOfElements];
		}
		for (size_t i=0;i<nbrOfElements;i++)
			values[i]=Mat.at(i);
		delete[] Mat.dimSizes;
		delete[] Mat.values;
	}
}

template <typename Elem,std::size_t dim>
bool Matrix<Elem,dim>::validIndex(std::size_t dimension,std::ptrdiff_t index)const
{
	return (0<=index && index<getSizeOfDimension(dimension));
}

template <typename Elem,std::size_t dim>
std::size_t Matrix<Elem,dim>::calculateIndex(std::ptrdiff_t* operatValues)const
{
	std::size_t index=0;
	for (std::size_t i=0;i<getNbrOfDimensions();i++)
		index+=getSizeOfDimension(i)*operatValues[i];
	return index;
}
/*
template <typename Elem,std::size_t dim>
typename Matrix<Elem,dim>::MatrixAccess
Matrix<Elem,dim>::operator[](std::ptrdiff_t i)
{
	return MatrixAccess(*this,i);
}
*/

//=============================================================================
//Matrice à 1 dimension
//=============================================================================


template <typename Elem>
Matrix<Elem,1>::Matrix(Elem value,std::initializer_list<std::size_t> dims)
{
	if (validDimensions(dims)) //vérification des données
	{
		dimensions=1;
		dimSizes= new std::size_t[dimensions];
		dimSizes[0]=*dims.begin();
		nbrOfElements = dimSizes[0];
		values = new Elem[nbrOfElements];
		for (std::size_t i = 0; i < nbrOfElements; i++)
		//on remplit la matrice avec la valeur initiale fournie
		{
			values[i] = value;
		}
	}
	else
		throw std::range_error("Number of dimension passed not compatible with your dimension-list");

}

template <typename Elem>
Matrix<Elem,1>::Matrix(const Matrix& Mat)
{
	dimensions=1;
	dimSizes=new size_t[dimensions];
	dimSizes[0]=Mat.getSizeOfDimension(0);
	nbrOfElements=Mat.getNbrOfElements();
	values=new Elem[nbrOfElements];
	for (size_t i=0;i<nbrOfElements;i++)
		values[i]=Mat.at(i);
}

template <typename Elem>
Matrix<Elem,1>::Matrix(Matrix&& Mat)
{
	dimensions=Mat.dimensions;
	dimSizes=Mat.dimSizes;
	Mat.dimSizes=nullptr;
	nbrOfElements=Mat.nbrOfElements;
	values = Mat.values;
	Mat.values=nullptr;
}

template <typename Elem>
Matrix<Elem,1>::~Matrix()
{
	delete[] dimSizes;
	delete[] values;
}

template <typename Elem>
bool Matrix<Elem,1>::validDimensions(std::initializer_list<std::size_t> dims) const
{
	if (dims.size() == 1 )
	// dims ne peut avoir qu'une seule composante
	{
		if (dims.begin()<=0)	//une dimension doit être stricement positive
			throw std::range_error("Invalid dimension: size <= 0 ");
		else //cas si liste est vide
			return true;
	}
	else if (dims.size()==0) //cas si liste est vide
		throw std::length_error("No dimension specified");
	else
		return false;
}

template <typename Elem>
inline size_t Matrix<Elem,1>::getSizeOfDimension(std::size_t i)const
{
	if (i==0)
	{
		return dimSizes[i];
	}
	else
		throw std::out_of_range("Index out of range");
}

template <typename Elem>
inline size_t Matrix<Elem,1>::getNbrOfDimensions()const
{
	return dimensions;
}

template <typename Elem>
inline size_t Matrix<Elem,1>::getNbrOfElements() const
{
	return nbrOfElements;
}

template <typename Elem>
Matrix<Elem,1>& Matrix<Elem,1>::operator=(const Matrix& Mat)
{
	if (this!=&Mat)
	{
		if (nbrOfElements!=Mat.getNbrOfElements())
		{
			nbrOfElements=Mat.getNbrOfElements();
			delete[] values;
			values=new Elem[nbrOfElements];
		}
		for (size_t i=0;i<nbrOfElements;i++)
			values[i]=Mat.at(i);
	}
	return *this;
}


template <typename Elem>
Matrix<Elem,1>& Matrix<Elem,1>::operator=(Matrix&& Mat)
{
	if (this!=&Mat)
	{
		if (nbrOfElements!=Mat.getNbrOfElements())
		{
			nbrOfElements=Mat.getNbrOfElements();
			delete[] values;
			values=new Elem[nbrOfElements];
		}
		for (size_t i=0;i<nbrOfElements;i++)
			values[i]=Mat.at(i);
		delete[] Mat.dimSizes;
		delete[] Mat.values;
	}
}

template <typename Elem>
bool Matrix<Elem,1>::validIndex(std::ptrdiff_t index)const
{
	return (0<=index && index<getSizeOfDimension(0));
}

// template <typename Elem>
// std::size_t Matrix<Elem,1>::calculateIndex(std::ptrdiff_t* operatValues)const
// {
// 	std::size_t index=0;
// 	for (std::size_t i=0;i<getNbrOfDimensions;i++)
// 		index+=getSizeOfDimension(i)*operatValues[i];
// 	return index;
// }

template <typename Elem>
inline const Elem Matrix<Elem,1>::at(std::size_t i)const
{
	return values[i];
}

template <typename Elem>
inline Elem& Matrix<Elem,1>::at(std::size_t i)
{
	return values[i];
}

template <typename Elem>
const Elem Matrix<Elem,1>::operator[](std::ptrdiff_t i)const
{
	if (validIndex(i))
		return at(i);
	else
		throw std::out_of_range("Index out of range");
}

template <typename Elem>
Elem& Matrix<Elem,1>::operator[](std::ptrdiff_t i)
{
	if (validIndex(i))
		return at(i);
	else
		throw std::out_of_range("Index out of range");
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const Matrix<T,1>& M)
{
	out<<"[ ";
	for (size_t i=0;i<M.getSizeOfDimension(0);i++)
		out<<M.at(i);
	out<<" ]";
	return out;
}



//
