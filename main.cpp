#include "Matrix.cpp"
#include "OperatHandler.cpp"
#include "constOperatHandler.cpp"
#include "ShiftedIndexMatrix.cpp"
#include "sliceMatrix.cpp"
#include "sliceOperatHandler.cpp"
#include "constSliceOperatHandler.cpp"
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <memory>
#include <utility>

int main(){
	std::cout<<"Tests :"<<std::endl;
	//std::cout<<"==================================================="<<std::endl;
	std::cout<<"Construction de 3 matrices à 4 composantes avec données correctes : ";
	try{
		Matrix<int,4> m1(1,{1,2,3,4});
		Matrix<int,4> m2(m1);
		Matrix<int,4> m3=Matrix<int,4>(7,{4,4,4,4});
	}
	catch (std::exception& e){
		std::cout<<"Exception : "<<e.what()<<"\n";
	}
	std::cout<<"réussie\n";
	//std::cout<<"==================================================="<<std::endl;
	std::cout<<"Construction de 3 matrices à 1 composante avec données correctes : ";
	try{
		Matrix<int,1> m4(0,10);
		Matrix<int,1> m5(m4);
		Matrix<int,1> m6=Matrix<int,1>(100,5);
	}
	catch (std::exception& e){
		std::cout<<"Exception : "<<e.what()<<"\n";
	}
	std::cout<<"réussie\n";
	//std::cout<<"=================================================================="<<std::endl;
	std::cout<<"Construction d'une matrice constante à 3 composantes avec données correctes : ";
	try{
		Matrix<int,3> const m7(27,{3,3,3});
	}
	catch (std::exception& e){
		std::cout<<"Exception : "<<e.what()<<"\n";
	}
	std::cout<<"réussie\n";
	//std::cout<<"=================================================================="<<std::endl;
	std::cout<<"Construction d'une matrice constante à 1 composante avec données correctes : ";
	try{
		Matrix<int,1> const m8(27,{10});
	}
	catch (std::exception& e){
		std::cout<<"Exception : "<<e.what()<<"\n";
	}
	std::cout<<"réussie\n";
	//std::cout<<"=================================================================="<<std::endl;
	std::cout<<"Construction d'une matrice à 3 composantes avec données incorrectes : ";
	try{
		Matrix<int,3> const m7(27,{3,3,0});
	}
	catch (std::exception& e){
		std::cout<<"Exception : "<<e.what()<<"\n\n";
	}
	std::cout<<"Test des méthodes sur les matrices : \n";
	std::cout<<"";

	//std::cout<<"=================================================================="<<std::endl;
	//std::cout<<"Matrix<int,4> k=Matrix<int,4>(3,{9,9,9,9})"<<std::endl;
	ShiftedIndexMatrix<int,5> sm1(10,{2,2,2,2,2},{5,5,5,5,5});
	//std::cout<<"k.getSizeOfDimension(1) : "<<k.getSizeOfDimension(1)<<std::endl;
	//Matrix<int,5> t=Matrix<int,5>(0,{2,2,2,2,2});
	//k=t;
	//std::cout<<"==================================================="<<std::endl;
	//std::cout<<"Display Matrix p: "<<std::endl;
	//std::cout<<p<<std::endl;
	//std::cout<<"Display Matrix k: "<<std::endl;
	//std::cout<<k<<std::endl;
	//std::cout<<"==================================================="<<std::endl;
	/*
	Matrix<int,1> eent(5,{7});
	std::cout<<"Matrix<int,1> eent(5,{7})"<<std::endl;
	std::cout<<"eent.getNbrOfElements()"<<std::endl;
	std::cout<<eent.getNbrOfElements()<<std::endl;
	std::cout<<"operator[]"<<std::endl;
	eent[2]=6;
	std::cout<<eent[2]<<std::endl;
	std::cout<<eent<<std::endl;*/
	//std::cout<<"==================================================="<<std::endl;
	/*t[1][1][1][1][1]=9;
	k[0][0][0][0]=t[0][0][0][0][0];
	std::cout<<t[0][0][0][0][0]<<std::endl;
	std::cout<<t<<std::endl;*/
	const Matrix<int,5> konst(66,{3,3,3,3,3});
	std::cout<<konst[2][2][2][2][2]<<"\n";
	//std::cout<<"==================================================="<<std::endl;
	std::cout<<"index décalés : \n";
	ShiftedIndexMatrix<int,3> indi(4,{3,3,3},{-3,-3,-3});
	ShiftedIndexMatrix<int,3> tre(11,{2,2,2},{-2,-2,-2});
	//tre=indi;
	std::cout<<tre<<"\n";
	//tre=ShiftedIndexMatrix<int,3>(11,{2,2,2},{-1,0,0});
	//tre[-1][-2][-1][-1]=2;

	ShiftedIndexMatrix<int,2> okk(0,{2,2},{10,10});
	okk[10][11]=1;
	okk[11][10]=2;
	okk[11][11]=3;
	std::cout<<okk<<"\n";

	ShiftedIndexMatrix<int,1> e1(1,4,-2);
	e1[1]=6;
	std::cout<<e1<<"\n";
	std::cout<<e1[1]<<"\n";
	std::cout<<"==================================================="<<std::endl;
	std::cout<<"slices : \n";
	sliceMatrix<int,3> slic(indi,{{-3,-1},{-3,-1},{-3,-1}},{1,1,1});
//	std::pair<std::size_t,std::size_t> p1({2,2});
	tre=slic;
	//std::cout<<indi<<"\n";
	//std::cout<<tre<<"\n";
	for (int i=-3;i<0;i++){
		for (int j=-3;j<0;j++){
			for (int k=-3;k<0;k++){
				tre[i][j][k]=-1;
				//std::cout<<tre<<"\n";
				}
			}
		}
	//std::initializer_list<std::pair<std::size_t,std::size_t>> ilp({{2,2},{2,2},{2,2}});
	//sliceMatrix<int,3,3> slic2(4,{3,3,3},{0,0,0});
	ShiftedIndexMatrix<int,3> utz(slic);
	//std::cout<<utz<<"\n";
	const sliceMatrix<int,1> slic1(e1,{-1,1});
	//slic1[0]=99;
	std::cout<<slic1[0]<<"\n";
	slic[-2][-2][-2]=45;
	ShiftedIndexMatrix<int,3> itz(sliceMatrix<int,3>(indi,{{-3,-1},{-3,-1},{-3,-1}},{1,1,1}));
	//std::cout<<slic<<"\n";
	return 0;

}
