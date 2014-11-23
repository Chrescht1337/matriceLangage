#include "Matrix.cpp"
#include <iostream>
#include <stdexcept>

int main()
{
	Matrix<int,4> p=Matrix<int,4>(1,{1,2,3,4});
	Matrix<int,4> k=p;
	std::cout<<p.getSizeOfDimension(2)<<std::endl;
	std::cout<<p.getNbrOfDimensions()<<std::endl;
	Matrix<int,4> t=Matrix<int,4>(0,{2,2,2,2});
	k=t;
	std::cout<<k.getSizeOfDimension(3)<<std::endl;
	std::cout<<"allo"<<std::endl;
	k[0][0][0][0]=99;
	return 0;
}
