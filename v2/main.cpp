#include <cmath>
#include <iostream>
#include <fstream>
#include "sheme.h"

using namespace std;
int main() {
	int Nx = 200;
	int Np = 100;
	int Nt = 10000;
	double a = 10000.0;
	double Pmin = 0.01;
	double Pmax = 100.0;

	double **gn = new double* [Nx + 1];
	double **g = new double* [Nx + 1];
	for (int i = 0; i <= Nx; ++i) {
		g[i] = new double[Np];
		gn[i] = new double[Np];
		for (int j = 0; j < Np; j++) {
			g[i][j] = gn[i][j] = 0;
		}
	}
	double* x = new double [Nx + 1];
	double ymin = log(Pmin);
	double dy = log(Pmax / Pmin) / Np;

	//создание сетки по х
	double h1 = 0.5 * Nx / log(1.0 + a);
	for (int i = 1; i <= Nx / 2; i++) {
		x[i] = 1.0 - exp(-(1.0 * i - 0.5 * Nx) / h1);
	}
	for (int i = Nx / 2 + 1; i < Nx + 1; i++) {
		x[i] = exp((1.0 * i - 0.5 * Nx) / h1) - 1.0;
	}
	double dt = 0.001;

	for (int i = 1; i <= Nt; i++) {
		cout << i << endl;
		solver(a, ymin, x, dy, dt, Nx, Np, gn, g);
		double **tmp = gn;
		gn = g;
		g = gn;

	}

	ofstream outf1("fp4.dat");
	for (int k = 1; k < Np; k++) {
		double y = ymin + k * dy;
		outf1 << k << " " << g[Nx / 10][k]*exp(y) << " " << g[Nx / 2][k] * exp(y) << " " << g[(Nx * 9) / 10][k]*exp(y) << endl;
	}
	outf1.close();

	ofstream outf2("Nx.dat");
	outf2 << Nx << endl;
	outf2.close();

	ofstream outf3("Np.dat");
	outf3 << Np << endl;
	outf3.close();

	ofstream outf4("fp4full.dat");
	for (int i = 0; i < Np; i++) {
		double y = ymin + i * dy;
		outf4 << exp(y) / exp(ymin) << " ";

		for (int k = 1; k <= Nx; k++) {
			outf4 << g[k][i] * exp(y) << " ";
		}
		outf4 << endl;
	}
	outf4.close();

	ofstream outf5("x.dat");
	for (int i = 0; i < Nx + 1; i++) {
		outf5 << x[i] << endl;
	}
	outf5.close();

	return 0;
}
