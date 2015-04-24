#include "stat.h"
#include <thread>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include "coef.h"

double a(double x, double u) {
	return V(x);
}

double b(double x, double u) {
	return sqrt(2*kappa(x,u));
}


void solve_part(int tn, FILE* out) {
	const int num = 10000;
	int lag = 50000;

	double dt = 0.1;
	double sqrt_dt = sqrt(dt);

	double x = 0;

	for (int k = 1; k <= num/tn; k++) {
		double t = 0;
		printf("particle № %d\n", k);
		double x = 0;
		double u = 0;
		for (int j = 0; j < lag; j++, t += dt) {
			x += a(x, u)*dt + b(x,u)*rnd_g()*sqrt_dt;
			u += (-1.0/3.)*dVonDx(x)*dt;
		}
		fprintf(out, "%g %g\n", x, u);
		fflush(out);
	}

}

int main(int argc, char const *argv[]) {

	set_g_rnd_seed(time(0));
	/*FILE *out = fopen("V.out", "w");
	for (double i = 0.0; i <= 5000; i+=0.1) {
		fprintf(out, "%g\t%g\n", i, rnd_g());	

	}
	return 0;
	*/
	
	FILE *out = fopen("ito.out", "w");

	int tn = 2;
	std::thread** tr = new std::thread* [tn];
	for (int i = 0; i < tn; i++) {
		tr[i] = new std::thread(solve_part, tn, out);
		// solve_part(tn, out)
	}
  for (int i=0; i < tn; i++) {
    tr[i]->join();
  }

	
	
	// fprintf(out, "%g\t%g\n", x);
	fclose(out);


	return 0;
}
