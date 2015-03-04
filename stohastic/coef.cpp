#include <iostream>
#include <cmath>
#include "coef.h"
using namespace std;

double pi = 3.14159265358979323846;



double V(double x) {
	double coef = 8.0;

	// (-atan(x*coef) + pi/2) / pi * (3.0/4) + 1.4
	return (-atan(x*coef) + pi/2) / pi * (3.0/4) + 1.0/4;
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
	// double coef = 8.0;
	// return -0.238732*coef/(coef*coef*x*x + 1);
	double dx = 0.001;
	return (V(x+dx) - V(x))/dx;
}

double kappa(double x, double y) {
	double kappa0 = 5;
	return kappa0; //* exp(y);
}

double Qinj(double x, double dx, double y, double dy) {
//	cout<<x<<dx<<y<<dy;
	if ((x<0.1*dx) && (x>-0.1*dx) && (y<0.5*dy) && (y>-0.5*dy)) {
//		cout<<"Hello!";
		return 1.0;
	} else {
		return 0.0;
	}
}