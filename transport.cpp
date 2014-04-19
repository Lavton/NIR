#include "transport.h"
#include <cmath>
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
	VecLong f10;
	for (int i = 0; i < xN; ++i){
		f10.push_back(0);
	}
	f1.push_back(f10);
	for (int i = 1; i < f0.size(); ++i){
		CommonMethods::Instance().clear_corrent_u();
		long double thisP = CommonMethods::Instance().get_this_p();
		long double dlogP = CommonMethods::Instance().get_next_dlogp();
		A[0]=0;
		for (int j = 0; j < xN-1; ++j){
			double thisU = CommonMethods::Instance().get_this_u();
			double nextU = CommonMethods::Instance().get_next_u();
			long double dx = CommonMethods::Instance().get_next_dx();
			F[j]=f0[i][j]-1.0*(nextU-thisU)*dt*f1[i-1][j+1]/(3*dx*dlogP);
			if ((j == CommonMethods::Instance().get_p_inj_N()) && (i == CommonMethods::Instance().get_x_inj_N())){
				F[j]+=CommonMethods::Instance().get_Q0()*pow(thisP,4)*dt;
			}
			if (j > 0){
				A[j] = -(nextU - thisU)*dt*(4 + 1/dlogP)/(3*dx);
				A[j]-=CommonMethods::Instance().get_D0()*thisP*dt/(dx*dx);
				A[j]+=nextU*dt/dx;
			}
			C[j] = 1+2*CommonMethods::Instance().get_D0()*thisP*dt/(dx*dx)-nextU*dt/dx;
			B[j] = -dt*CommonMethods::Instance().get_D0()*thisP/(dx*dx);
		}
		F[f0[i].size()-1]=0;
		A[f0[i].size()-1]=0;
		C[f0[i].size()-1]=0;
		B[f0[i].size()-1] = 0;
		f1.push_back(CommonMethods::matrixSolver(A,B,C,F));
//		f1[i].reserve(f0[i].size());
	}
	return f1;
}
