#include "sheme.h"
#include <thread>
#include <iostream>
#include "coef.h"
#include "progon.h"
#include "data_storage.h"
#include <iostream>
#include <cmath>
using namespace std;



void solve_part(int i, int tn, long double a, long double ymin, long double* x, long double dy,
                long double dt, int Nx, int Np, long double** gn, long double** g) {

	int begin = i * Np / tn;
	int end = (i + 1) * Np / tn;
	long double *A = DataStorage::Instance(Nx, tn).A[i];
	long double *C = DataStorage::Instance(Nx, tn).C[i];
	long double *B = DataStorage::Instance(Nx, tn).B[i];
	long double *F = DataStorage::Instance(Nx, tn).F[i];
	long double *Xg = DataStorage::Instance(Nx, tn).Xg[i];
	long double *alpha = DataStorage::Instance(Nx, tn).alpha[i];
	long double *beta = DataStorage::Instance(Nx, tn).beta[i];

	for (int k = begin; k < end; ++k) {
		long double y = ymin + k * dy;
		long double gkp = gn[1][k];
		long double gkm = (k == 1) ? 0.0 : gn[1][k - 1];
		long double dx = (x[2] + a) / 2.0;
		long double dxp = x[2] - x[1];
		long double dxm = x[1] + a;
		long double xp = (x[2] + x[1]) / 2.0;
		long double xm = (x[1] - a) / 2.0;
		long double gip = (gn[2][k] + gn[1][k]) / 2.0;
		long double gim = gn[1][k] / 2.0;


		C[1] = 1.0 + (dt / (2.0 * dx)) * (kappa(xp, y) / dxp + kappa(xm, y) / dxm);
		B[1] = -(dt / (2.0 * dx)) * (kappa(xp, y) / dxp);
		F[1] = gn[1][k] + (dt / (2.0 * dx)) * (kappa(xp, y) * gn[2][k] / dxp) -
		       (dt / (2.0 * dx)) * (kappa(xp, y) / dxp +
		                            kappa(xm, y) / dxm) * gn[1][k] - (dt / dx) * (u(xp) * gip -
		                                    u(xm) * gim) + (dt / 3.0) * ((u(xp) - u(xm)) / dx) *
		       ((gkp - gkm) / dy) + dt * Qinj(x[1], dx, y, dy);
		for (int i = 2; i < Nx; i++) {
			gkp = gn[i][k];
			gkm = (k == 1) ? 0.0 : gn[i][k - 1];
			dx = (x[i + 1] - x[i - 1]) / 2.0;
			dxp = x[i + 1] - x[i];
			dxm = x[i] - x[i - 1];
			xp = (x[i + 1] + x[i]) / 2.0;
			xm = (x[i] + x[i - 1]) / 2.0;
			gip = (gn[i + 1][k] + gn[i][k]) / 2.0;
			gim = (gn[i][k] + gn[i - 1][k]) / 2.0;
			A[i - 1] = -(dt / (2.0 * dx)) * (kappa(xm, y) / dxm);
			C[i] = 1.0 + (dt / (2.0 * dx)) * (kappa(xp, y) / dxp + kappa(xm, y) / dxm);
			B[i] = -(dt / (2.0 * dx)) * (kappa(xp, y) / dxp);
			F[i] = gn[i][k] + (dt / (2.0 * dx)) * (kappa(xp, y) *
			                                       (gn[i + 1][k] - gn[i][k]) / dxp - kappa(xm, y) *
			                                       (gn[i][k] - gn[i - 1][k]) / dxm) - (dt / dx) *
			       (u(xp) * gip - u(xm) * gim) + (dt / 3.0) * ((u(xp) -
			               u(xm)) / dx) * ((gkp - gkm) / dy) + dt * Qinj(x[i], dx, y, dy);
		}
		gkp = gn[Nx][k];
		gkm = (k == 1) ? 0.0 : gn[Nx][k - 1];
		dx = (x[Nx] - x[Nx - 1]) / 2.0;
		dxm = x[Nx] - x[Nx - 1];
		xp = x[Nx];
		xm = (x[Nx] + x[Nx - 1]) / 2.0;
		gip = gn[Nx][k];
		gim = (gn[Nx][k] + gn[Nx - 1][k]) / 2.0;
		A[Nx - 1] = -(dt / (2.0 * dx)) * (kappa(xm, y) / dxp);
		C[Nx] = 1.0 + (dt / (2.0 * dx)) * (kappa(xm, y) / dxm);

		F[Nx] = gn[Nx][k] - (dt / (2.0 * dx)) * (kappa(xm, y) *
		        (gn[Nx][k] - gn[Nx - 1][k]) / dxm) - (dt / dx) *
		        (u(xp) * gip - u(xm) * gim) + (dt / 3.0) * ((u(xp) -
		                u(xm)) / dx) * ((gkp - gkm) / dy) + dt * Qinj(x[Nx], dx, y, dy);

		matrix_solver(A, C, B, Nx - 1, F, Xg, alpha, beta);
		for (int l = 0; l < Nx + 1; ++l) {
			g[l][k] = Xg[l];
		}
	}
}
void solver(long double a, long double ymin, long double* x, long double dy,
            long double dt, int Nx, int Np, long double** gn, long double** g) {
	int tn = 4;
	std::thread** tr = new std::thread* [4];
	for (int i = 0; i < tn; i++) {
		tr[i] = new std::thread(solve_part, i, tn, a, ymin, x, dy, dt, Nx, Np, gn, g);
		// solve_part(i, tn, a, ymin, x, dy, dt, Nx, Np, gn, g);
	}
	for (int i = 0; i < tn; i++) {
		tr[i]->join();
	}

}
