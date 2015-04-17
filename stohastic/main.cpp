#include "stat.h"
#include <stdio.h>
#include <math.h>
#include <ctime>
#include "coef.h"

double a(double x, double y) {
	return V(x);
}

double b(double x, double y) {
	return sqrt(2*kappa(x,y));
}

int main(int argc, char const *argv[]) {

	set_g_rnd_seed(time(0));
	/*FILE *out = fopen("V.out", "w");
	for (double i = 0.0; i <= 5000; i+=0.1) {
		fprintf(out, "%g\t%g\n", i, rnd_g());	

	}
	return 0;
	*/
	double step = 0.25;
	const int num = 50000;
	int lag = 20000;
	FILE *out = fopen("ito.out", "w");

	double dt = 0.1;
	double sqrt_dt = sqrt(dt);

	double x = 0;
	double* xs = new double[num];
	double* us = new double[num];
	
	
	// fprintf(out, "%g\t%g\n", x);
	for (int k = 1; k <= num; k++) {
		double t = 0;
		printf("particle № %d\n", k);
		double x = 0;
		double u = 0;
		for (int j = 0; j < lag; j++, t += dt) {
			x += a(x, t)*dt + b(x,t)*rnd_g()*sqrt_dt;
			u += (-1.0/3)*dVonDx(x)*dt;
		}
		xs[k-1] = x;
		us[k-1] = u;
		fprintf(out, "%g %g\n", x, u);
		fflush(out);
	}
	fclose(out);


	return 0;
}
