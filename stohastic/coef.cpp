#include <iostream>
#include <cmath>
#include "coef.h"
using namespace std;

double pi = 3.14159265358979323846;



double V(double x) {
	double coef = 0.25;

	double u1, u2;
	u1 = 1.0;
	u2 = 0.25 * u1;
	return (u1 + u2) / 2. - (u1 - u2) / 2.*tanh(x / coef);


	// return (1/4)+((3/4)*(1-tanh(x/coef))/2);
	// (-atan(x*coef) + pi/2) / pi * (3.0/4) + 1.4
	// return (-atan(x*coef) + pi/2) / pi * (3.0/4) + 1.0/4;
	/*	double u1, u2;
		u1=1.0;
		u2=0.25*u1;
		if (x<0.0) {
			return u1;
		} else {
			return u2;
		}
	*/
}

double dVonDx(double x) {
	double coef = 0.25;

	double u1, u2;
	u1 = 1.0;
	u2 = 0.25 * u1;
	double dx = 0.001;
	return -(u1 - u2) / 2. / coef / cosh(x / coef) / cosh(x / coef) ;

	// return -0.238732*coef/(coef*coef*x*x + 1);

	// double dx = 0.000001;
	// return (V(x+dx) - V(x))/dx;
	/*	double ch = cosh(x/coef);
		return (-0.75/2)/coef/ch/ch;
	*/

}

double kappa(double x, double u) {
	double kappa0 = 5;
	return kappa0 * exp(u);
}