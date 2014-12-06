#include "Matrix.cpp"
#include "OperatHandler.cpp"
#include "constOperatHandler.cpp"
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <memory>

int main()
{
	std::cout<<"Tests :"<<std::endl;
	std::cout<<"==================================================="<<std::endl;
	std::cout<<"Matrix<int,4> p(1,{1,2,3,4})"<<std::endl;
	Matrix<int,4> p(1,{1,2,3,4});
	std::cout<<p.getSizeOfDimension(2)<<std::endl;
	std::cout<<p.getNbrOfDimensions()<<std::endl;
	std::cout<<"==================================================="<<std::endl;
	std::cout<<"Matrix<int,4> k=Matrix<int,4>(3,{9,9,9,9})"<<std::endl;
	Matrix<int,4> k=Matrix<int,4>(3,{9,9,9,9});
	std::cout<<"k.getSizeOfDimension(1) : "<<k.getSizeOfDimension(1)<<std::endl;
	std::cout<<k.getSizeOfDimension(3)<<std::endl;
	std::cout<<"==================================================="<<std::endl;
	Matrix<int,5> t=Matrix<int,5>(0,{2,2,2,2,2});
	//k=t;
	std::cout<<"==================================================="<<std::endl;
	std::cout<<"Display Matrix p: "<<std::endl;
	std::cout<<p<<std::endl;
	std::cout<<"Display Matrix k: "<<std::endl;
	//std::cout<<k<<std::endl;
	std::cout<<"==================================================="<<std::endl;
	std::cout<<"Matrice à une dimension"<<std::endl;
	Matrix<int,1> eent(5,{7});
	std::cout<<"Matrix<int,1> eent(5,{7})"<<std::endl;
	std::cout<<"eent.getNbrOfElements()"<<std::endl;
	std::cout<<eent.getNbrOfElements()<<std::endl;
	std::cout<<"operator[]"<<std::endl;
	eent[2]=6;
	std::cout<<eent[2]<<std::endl;
	std::cout<<eent<<std::endl;
	std::cout<<"==================================================="<<std::endl;
	t[0][0][0][0][0]=9;
	k[0][0][0][0]=t[0][0][0][0][0];
	std::cout<<t[0][0][0][0][0]<<std::endl;
	std::cout<<t<<std::endl;
	const Matrix<int,5> konst(66,{3,3,3,3,3});
	std::cout<<konst[2][2][2][2][2]<<"\n";
	return 0;

}
