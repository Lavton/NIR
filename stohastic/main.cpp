#include "stat.h"
#include <stdio.h>
#include <math.h>
#include <ctime>

double a(double x, double y) {
	return 0;
}
double b(double x, double y) {
	return x;
}

int main(int argc, char const *argv[]) {
	set_g_rnd_seed(time(0));

	double step = 0.1;
	const int num = 100;
	int lag = 1000;
	FILE *out = fopen("ito.out", "w");

	double dt = step / lag;
	double sqrt_dt = sqrt(dt);

	double x = 1;
	double t = 0; 

	fprintf(out, "%g\t%g\n", t, x);
	for (int k = 1; k <= num; k++) {
		for (int j = 0; j < lag; j++, t += dt) {
			x += a(x, t)*dt + b(x,t)*rnd_g()*sqrt_dt;
		}
		fprintf(out, "%g\t%g\n", t, x);
		fflush(out);
	}
	fclose(out);
	return 0;
}
