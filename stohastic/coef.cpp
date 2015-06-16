#include <iostream>
#include <cmath>
#include "coef.h"
using namespace std;

// long double pi = 3.14159265358979323846;
// long double x0 = pow(10, 17);
// long double V0 = 5000.0 * 1000 * 100;
// long double t0 = 3.0 * pow(10, 7);
// long double k0 = pow(10, 28);


long double V(long double x) {
	long double coef = 0.25;

	long double u1, u2;
	u1 = 1.0;
	u2 = 0.25 * u1;
	return (u1 + u2) / 2. - (u1 - u2) / 2.*tanh(x / coef);


	// return (1/4)+((3/4)*(1-tanh(x/coef))/2);
	// (-atan(x*coef) + pi/2) / pi * (3.0/4) + 1.4
	// return (-atan(x*coef) + pi/2) / pi * (3.0/4) + 1.0/4;
	/*	long double u1, u2;
		u1=1.0;
		u2=0.25*u1;
		if (x<0.0) {
			return u1;
		} else {
			return u2;
		}
	*/
}

long double dVonDx(long double x) {
	long double coef = 0.25;

	long double u1, u2;
	u1 = 1.0;
	u2 = 0.25 * u1;
	long double dx = 0.001;
	return -(u1 - u2) / 2. / coef / cosh(x / coef) / cosh(x / coef) ;

	// return -0.238732*coef/(coef*coef*x*x + 1);

	// long double dx = 0.000001;
	// return (V(x+dx) - V(x))/dx;
	/*	long double ch = cosh(x/coef);
		return (-0.75/2)/coef/ch/ch;
	*/

}

long double kappa(long double x, long double u) {
	long double kappa0 = 3.0;
	return kappa0 * exp(u);
}