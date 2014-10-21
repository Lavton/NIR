#include "sheme.h"
#include <iostream>
#include "coef.h"
#include "progon.h"
using namespace std;
void solver(double a, double ymin, double* x, double dy, 
	double dt, int Nx, int Np, double** gn, double** g) {

	double *A = new double[Nx];
	double *C = new double[Nx + 1];
	double *B = new double[Nx];
	double *F = new double[Nx + 1];
	double *Xg = new double[Nx + 1];
	for (int k = 1; k < Np; ++k) {
		double y = ymin + k * dy;
		double gkp = gn[1][k];
		double gkm = (k == 1) ? 0.0 : gn[1][k - 1];
		double dx = (x[2] + a) / 2.0;
		double dxp = x[2] - x[1];
		double dxm = x[1] + a;
		double xp = (x[2] + x[1]) / 2.0;
		double xm = (x[1] - a) / 2.0;
		double gip = (gn[2][k] + gn[1][k]) / 2.0;
		double gim = gn[1][k] / 2.0;

		C[1] = 1.0 + (dt / (2.0 * dx)) * (kappa(xp, y) / dxp + kappa(xm,y) / dxm);
		B[1] = -(dt / (2.0 * dx)) * (kappa(xp, y) / dxp);
		F[1] = gn[1][k] + (dt / (2.0 * dx)) * (kappa(xp, y) * gn[2][k] / dxp) -
			(dt / (2.0 * dx)) * (kappa(xp, y) / dxp + 
			kappa(xm, y) / dxm) *gn[1][k] - (dt / dx) * (u(xp) * gip - 
			u(xm) * gim) + (dt / 3.0) * ((u(xp) - u(xm)) / dx) * 
			((gkp - gkm) / dy) + dt * Qinj(x[1], dx, y, dy);
		for (int i = 2; i < Nx; i++) {
			gkp=gn[i][k];
			gkm = (k == 1) ? 0.0 : gn[i][k - 1];
			dx = (x[i + 1] - x[i - 1]) / 2.0;
			dxp = x[i + 1] - x[i];
			dxm = x[i] - x[i - 1];
			xp = (x[i+1] + x[i]) / 2.0;
			xm=(x[i]+x[i-1]) / 2.0;
			gip = (gn[i + 1][k] + gn[i][k]) / 2.0;
			gim = (gn[i][k] + gn[i - 1][k]) / 2.0;
			A[i-1] = -(dt / (2.0 * dx)) * (kappa(xm, y) / dxm);
			C[i] = 1.0 + (dt / (2.0 * dx)) * (kappa(xp, y) / dxp + kappa(xm, y) / dxm);
			B[i] = -(dt / (2.0 * dx)) * (kappa(xp, y) / dxp);
			F[i] = gn[i][k] + (dt / (2.0 * dx)) * (kappa(xp, y) * 
				(gn[i+1][k] - gn[i][k]) / dxp - kappa(xm, y) * 
        		(gn[i][k] - gn[i-1][k]) / dxm) - (dt / dx) * 
				(u(xp) * gip - u(xm) * gim) + (dt / 3.0) * ((u(xp) -
				u(xm)) / dx) * ((gkp - gkm) / dy) + dt * Qinj(x[i],dx,y,dy);
		}
		gkp = gn[Nx][k];
		gkm = (k == 1) ? 0.0 : gn[Nx][k - 1];
		dx = (x[Nx] - x[Nx - 1]) / 2.0;
		dxm = x[Nx] - x[Nx - 1];
		xp=x[Nx];
		xm=(x[Nx] + x[Nx-1]) / 2.0;
		gip = gn[Nx][k];
		gim = (gn[Nx][k] + gn[Nx - 1][k]) / 2.0;
		A[Nx - 1] = -(dt / (2.0 * dx)) * (kappa(xm, y) / dxp);
		C[Nx] = 1.0 + (dt / (2.0 * dx)) * (kappa(xm, y) / dxm);

		F[Nx] = gn[Nx][k] - (dt / (2.0 * dx)) * (kappa(xm, y) * 
			(gn[Nx][k] - gn[Nx-1][k]) / dxm) - (dt / dx) *
    		(u(xp) * gip - u(xm) * gim) + (dt / 3.0) * ((u(xp) -
    		u(xm)) / dx) * ((gkp - gkm) / dy) + dt * Qinj(x[Nx],dx,y,dy);

    	matrix_solver(A, C, B, Nx - 1, F, Xg);
    	for (int l = 0; l < Nx + 1; ++l) {
    		g[l][k] = Xg[l];
    	}
	}
	delete[] A;
	delete[] C;
	delete[] B;
	delete[] F;
	delete[] Xg;
}