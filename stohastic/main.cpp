#include "stat.h"
#include <thread>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include "coef.h"


long double x0 = pow(10, 17);
long double V0 = 5000.0 * 1000 * 100;
long double t0 = 3.0 * pow(10, 7);
long double k0 = pow(10, 28);

long double a(long double x, long double u) {
	return V(x)*(V0*t0/x0);
}

long double b(long double x, long double u) {
	return sqrt(2 * kappa(x, u))*sqrt(k0*t0)/x0;

}


void solve_part(int tn, FILE* out) {
	const int num = 50000;
	int lag = 200000;
	static int part_num = 0;
	long double dt = 0.9;
	long double sqrt_dt = sqrt(dt);

	long double x = 0;

	for (int k = 1; k <= num / tn; k++) {
		long double t = 0;
		++part_num;
		if (!(part_num % 100)) {
			printf("particle № %d\n", ++part_num);
			system("./hist_builder.py");
			if (part_num > 6500/2) {
				exit(0);
			}
		}
		long double x = 0;
		long double u = 0;
		for (int j = 0; j < lag; j++, t += dt) {
			x += a(x, u) * dt + b(x, u) * rnd_g() * sqrt_dt;
			u += ((-1.0 / 3.) * dVonDx(x)/* - 0.00004 * sqrt(1 + exp(2 * u))*/) * dt*t0*(V0/x0);
			// printf("%f %f\n", exp(2*u), sqrt(1+exp(2*u)));
		}
		fprintf(out, "%Lg %Lg\n", x, u);
		fflush(out);
	}

}

int main(int argc, char const *argv[]) {

	set_g_rnd_seed(time(0));
	/*FILE *out = fopen("V.out", "w");
	for (long double i = 0.0; i <= 5000; i+=0.1) {
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
	for (int i = 0; i < tn; i++) {
		tr[i]->join();
	}



	// fprintf(out, "%g\t%g\n", x);
	fclose(out);


	return 0;
}
