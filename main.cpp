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
	std::cout<<"Construction de 3 matrices à 4 composantes avec données correctes : ";
	try{
		Matrix<int,4> m1(1,{1,2,3,4});
		Matrix<int,4> m2(m1);
		Matrix<int,4> m3=Matrix<int,4>(7,{4,4,4,4});
	}
	catch (std::exception& e){
		std::cout<<"Exception : "<<e.what()<<"\n";
	}
	std::cout<<"réussite\n";

	std::cout<<"Construction de 3 matrices à 1 composante avec données correctes : ";
	try{
		Matrix<int,1> m4(0,10);
		Matrix<int,1> m5(m4);
		Matrix<int,1> m6=Matrix<int,1>(100,5);
	}
	catch (std::exception& e){
		std::cout<<"Exception : "<<e.what()<<"\n";
	}
	std::cout<<"réussite\n";

	std::cout<<"Construction d'une matrice constante à 3 composantes avec données correctes : ";
	try{
		Matrix<int,3> const m7(27,{3,3,3});
	}
	catch (std::exception& e){
		std::cout<<"Exception : "<<e.what()<<"\n";
	}
	std::cout<<"réussite\n";

	std::cout<<"Construction d'une matrice constante à 1 composante avec données correctes : ";
	try{
		Matrix<int,1> const m8(27,10);
	}
	catch (std::exception& e){
		std::cout<<"Exception : "<<e.what()<<"\n";
	}
	std::cout<<"réussite\n";

	std::cout<<"Construction d'une matrice à 3 composantes avec données incorrectes : ";
	try{
		Matrix<int,3> const m7(27,{3,3,0});
	}
	catch (std::exception& e){
		std::cout<<"Exception : "<<e.what()<<"\n\n";
	}
	std::cout<<"Test des méthodes sur les matrices : \n";

	Matrix<int,4> m1(1,{1,2,3,4});
	Matrix<int,4> m2(m1);
	Matrix<int,4> m3=Matrix<int,4>(7,{2,2,2,2});
	std::cout<<"Matrice m3 : "<<"\n";
	std::cout<<m3<<"\n";
	std::cout<<"Nombre de dimension de m3 : "<<m3.getNbrOfDimensions()<<"\n";
	std::cout<<"Nombre d'éléments de m3 : "<<m3.getNbrOfElements()<<"\n";
	std::cout<<"Grandeur de la 3eme composante de m3 : "<<m3.getSizeOfDimension(2)<<"\n";
	std::cout<<"m3[1][0][1][0]= -11\n";
	m3[1][0][1][0]=-11;
	std::cout<<m3<<"\n";
	std::cout<<"Matrice m1 : "<<m1<<"\n";
	std::cout<<"Assignation de m3 à m1 : \n";
	m1=Matrix<int,4>(m3);
	std::cout<<"m1 : "<<m1<<"\n\n";


	std::cout<<"Tests sur les matrices avec indices décalés : \n";
	std::cout<<"Construction de plusieurs matrices à 3 composantes avec indices décalés utilisant des données correctes : \n";
	try{
		ShiftedIndexMatrix<int,3> sm1(10,{2,2,2},{5,5,5});
		ShiftedIndexMatrix<int,3> sm2(sm1);
		ShiftedIndexMatrix<int,3> sm3=ShiftedIndexMatrix<int,3>(-5,{3,3,3},{-5,-5,-5});
		Matrix<int,3> m7(27,{3,3,3});
		ShiftedIndexMatrix<int,3> sm4(m7);
		ShiftedIndexMatrix<int,3> sm5=Matrix<int,3>(7,{2,2,2});
	}
	catch (std::exception& e){
		std::cout<<"Exception : "<<e.what()<<"\n";
	}
	std::cout<<"réussite\n";

	std::cout<<"Construction de plusieurs matrices à 1 composantes avec indices décalés utilisant des données correctes : \n";
	try{
		ShiftedIndexMatrix<int,1> sm6(10,8,-8);
		ShiftedIndexMatrix<int,1> sm7(sm6);
		ShiftedIndexMatrix<int,1> sm8=ShiftedIndexMatrix<int,1>(-5,12,20);
		Matrix<int,1> m7(27,10);
		ShiftedIndexMatrix<int,1> sm9(m7);
		ShiftedIndexMatrix<int,1> sm10=Matrix<int,1>(3,10);
	}
	catch (std::exception& e){
		std::cout<<"Exception : "<<e.what()<<"\n";
	}
	std::cout<<"réussite\n";

	std::cout<<"Construction d'une matrice constante à 3 composantes avec indices décalés utilisant des données correctes : \n";
	try{
		ShiftedIndexMatrix<int,3> const sm1(10,{2,2,2},{5,5,5});
	}
	catch (std::exception& e){
		std::cout<<"Exception : "<<e.what()<<"\n";
	}
	std::cout<<"réussite\n";

	std::cout<<"Construction d'une matrice constante à 1 composante avec indices décalés utilisant des données correctes : \n";
	try{
		ShiftedIndexMatrix<int,1> const sm6(10,8,-8);
	}
	catch (std::exception& e){
		std::cout<<"Exception : "<<e.what()<<"\n";
	}
	std::cout<<"réussite\n";

	std::cout<<"Construction d'une matrice à 3 composantes avec indices décalés utilisant des données incorrectes : \n";
	try{
		ShiftedIndexMatrix<int,3> sm1(10,{2,2,2},{5,5});
	}
	catch (std::exception& e){
		std::cout<<"Exception : "<<e.what()<<"\n\n";
	}
	std::cout<<"Construction de matrices sur lesquelles on peut faire des tranches utilisant des données correctes : \n";
	try{
		Matrix<int,4> m3(7,{2,2,2,2});
		sliceMatrix<int,4> slm1(m3,{{0,1},{0,1},{0,1},{0,1}});
		sliceMatrix<int,4> slm2(m3,{{0,1},{0,1},{0,1},{0,1}},{1,2,1,1});
		ShiftedIndexMatrix<int,3> sm1(10,{2,2,2},{5,5,5});
		sliceMatrix<int,3> slm3(sm1,{{5,6},{5,6},{5,6}});
		sliceMatrix<int,3> slm4(sm1,{{5,6},{5,6},{5,6}},{7,7,7});
		sliceMatrix<int,3> slm5(slm3);
		sliceMatrix<int,3> slm6=sliceMatrix<int,3>(sm1,{{5,6},{5,6},{5,6}},{7,7,7});

		Matrix<int,1> m4(0,10);
		sliceMatrix<int,1> slm7(m4,{2,5});
		sliceMatrix<int,1> slm8(m4,{2,5},2);
		ShiftedIndexMatrix<int,1> sm6(10,8,-8);
		sliceMatrix<int,1> slm9(sm6,{-5,-2});
		sliceMatrix<int,1> slm10(sm6,{-5,-2},2);
		sliceMatrix<int,1> slm11(slm10);
		sliceMatrix<int,1> slm12=sliceMatrix<int,1>(slm11);
	}
	catch (std::exception& e){
		std::cout<<"Exception : "<<e.what()<<"\n";
	}
	std::cout<<"réussite\n";

	std::cout<<"Construction de matrices sur lesquelles on peut faire des tranches utilisant des données incorrectes : \n";
	try{
		Matrix<int,4> m3(7,{2,2,2,2});
		sliceMatrix<int,4> slm1(m3,{{0,1},{0,1},{0,1},{7,1}});
	}
	catch (std::exception& e){
		std::cout<<"Exception : "<<e.what()<<"\n\n";
	}
	sliceMatrix<int,4> slm1(m3,{{0,1},{0,1},{0,1},{0,1}});
	std::cout<<"Matrice slm1 : ";
	std::cout<<slm1<<"\n";
	std::cout<<"slm1[0][0][0][0]=27 \n";
	slm1[0][0][0][0]=27;
	std::cout<<slm1<<"\n";

	std::cout<<"Assignations de tranches à des matrices à index décalés : \n";
	try{
		Matrix<int,4> m1(1,{1,2,3,4});
		ShiftedIndexMatrix<int,4> sm8=sliceMatrix<int,4>(m1,{{0,0},{0,1},{0,1},{0,1}});
		sm8[0][0][0][0]=22;
		std::cout<<sm8<<"\n";
	}
	catch (std::exception& e){
		std::cout<<"Exception : "<<e.what()<<"\n\n";
	}
	std::cout<<"réussite\n";

	std::cout<<"Essais d'accéder aux éléments des différents matrices : \n";
	try{
		Matrix<int,4> m3(7,{2,2,2,2});
		m3[0][0][0][0]=-11;
		Matrix<int,4> const m20(7,{2,2,2,2});
		m20[0][0][0][0]==7;
		Matrix<int,1> m4(0,10);
		m4[0]=4;
		Matrix<int,1> const m40(0,10);
		if (m40[0]==0)
			std::cout<<"Operateur [] réussi\n";
		ShiftedIndexMatrix<int,3> sm1(10,{2,2,2},{5,5,5});
		sm1[6][6][6]=111;
		ShiftedIndexMatrix<int,3> const sm20(10,{2,2,2},{5,5,5});
		if (sm20[6][6][6]==10)
			std::cout<<"Operateur [] réussi\n";
		ShiftedIndexMatrix<int,1> sm6(10,8,-8);
		sm6[-4]=20;
		ShiftedIndexMatrix<int,1> const sm60(10,8,-8);
		if (sm60[-4]==10)
			std::cout<<"Operateur [] réussi\n";
		sliceMatrix<int,4> slm1(m3,{{0,1},{0,1},{0,1},{0,1}});
		slm1[0][0][0][0]=90;
		sliceMatrix<int,4> const slm10(m3,{{0,1},{0,1},{0,1},{0,1}});
		if (slm10[0][0][0][0]==7)
			std::cout<<"Operateur [] réussi\n";


	}
	catch (std::exception& e){
		std::cout<<"Exception : "<<e.what()<<"\n";
	}
	std::cout<<"réussite\n";

	Matrix<int,2>* mmm;
	mmm= new ShiftedIndexMatrix<int,2>(5,{2,2},{1,1});
	delete mmm;
	return 0;

}
