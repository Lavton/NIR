#include "transport.h"
#include <cmath>
#include <stdio.h>
#include "common.h"
#include <iostream>
using namespace std;
MatrixVector init(){
	MatrixVector v;
	int pN=CommonMethods::Instance().get_p_numbers();
	int xN=CommonMethods::Instance().get_x_numbers();

	for (int i = 0; i < pN; ++i)
	{

		VecLong v0(xN);
		for (int j = 0; j < xN; ++j){
			v0[j]=0;
		}
		v.push_back(v0);

	}
	return v;
}

MatrixVector first_kind_nonclear(const MatrixVector &f0){

	MatrixVector f1; //(f0.size());
	int xN = f0[0].size();
	VecLong A(xN);
	VecLong B(xN);
	VecLong C(xN);
	VecLong F(xN);
	long double dt = CommonMethods::Instance().get_next_dt();
	long double D0 = CommonMethods::Instance().get_D0();
	VecLong f10;
	for (int i = 0; i < xN; ++i){
		f10.push_back(0);
	}
	f1.push_back(f10);
	for (int i = 1; i < f0.size(); ++i){
		CommonMethods::Instance().clear_corrent_u();
		long double thisP = CommonMethods::Instance().p[i];
		long double dlogP = CommonMethods::Instance().get_next_dlogp();
		long double dx = CommonMethods::Instance().get_next_dx();
		A[0]=0;
		C[0]=-1/dt - CommonMethods::Instance().u[0]/dx - D0* thisP*thisP/(dx*dx);
		B[0]=D0*thisP/(dx*dx);
		F[0]=-f0[i][0];
		for (int j = 1; j < xN-2; ++j){
			double prevU = CommonMethods::Instance().u[j-1];
			double thisU = CommonMethods::Instance().u[j];
			A[j] = thisU/dx + D0*thisP/(dx*dx);
			C[j] = (thisU-prevU)/(3.0*dx*dlogP)+(4*(thisU-prevU))/(3*dx);
			C[j] = C[j] - 1/dt - thisU/dx - D0*thisP*thisP/(dx*dx);
			B[j]=D0*thisP/(dx*dx);
			F[j]=-f0[i][j]/dt - (f1[i-1][j]/3.0)*(thisU-prevU)/dlogP;
			if ((j == CommonMethods::Instance().get_p_inj_N()) && (i == CommonMethods::Instance().get_x_inj_N())){
				F[j]+=CommonMethods::Instance().get_Q0()*pow(thisP,4);
			}
		}
		double prevU = CommonMethods::Instance().u[xN-2];
		double thisU = CommonMethods::Instance().u[xN-1];
		A[xN-1] = thisU/dx + D0*thisP/(dx*dx);
		C[xN-1] = (thisU-prevU)/(3.0*dx*dlogP)+(4*(thisU-prevU))/(3*dx);
		C[xN-1] = C[xN-1] - 1/dt - thisU/dx - D0*thisP*thisP/(dx*dx);
		B[xN-1] = 0;
		F[xN-1]=-f0[i][xN-1]/dt - (f1[i-1][xN-1]/3.0)*(thisU-prevU)/dlogP;
		if ((xN-1 == CommonMethods::Instance().get_p_inj_N()) && (i == CommonMethods::Instance().get_x_inj_N())){
			F[xN-1]+=CommonMethods::Instance().get_Q0()*pow(thisP,4);
		}
//	cout<<"Here\n";
		cout<<"A = ";
		CommonMethods::printVecLong(A);
		cout<<"C = ";
		CommonMethods::printVecLong(C);
		cout<<"B = ";
		CommonMethods::printVecLong(B);
		cout<<"F = ";
		CommonMethods::printVecLong(F);

//		CommonMethods::printMatrixVector(f0);
		getchar();
		f1.push_back(CommonMethods::matrixSolver(A,B,C,F));
//		f1[i].reserve(f0[i].size());
	}
	return f1;
}
