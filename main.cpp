#include "Matrix.cpp"
#include "HelperMatrix.cpp"
#include <iostream>
#include <stdexcept>

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
	Matrix<int,4> t=Matrix<int,4>(0,{2,2,2,2});
	//std::cout<<"allo"<<std::endl;
	//k[0][0][0][0]=99;
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
	HelperMatrix<int,4> mmm(k);
	std::cout<<"";
	return 0;
}
