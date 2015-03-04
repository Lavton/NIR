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
/*	FILE *out = fopen("V.out", "w");
	for (double i = 0.0; i <= 5.0; i+=0.1) {
		fprintf(out, "%g\t%g\n", i, V(i));	

	}
	return 0;
*/	
	double step = 0.1;
	const int num = 1000;
	int lag = 20000;
	FILE *out = fopen("ito.out", "w");

	double dt = 0.01;
	double sqrt_dt = sqrt(dt);

	double x = 0;
	
	
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

		fprintf(out, "%g\n", u);
		fflush(out);
	}
	fclose(out);
	return 0;
}
