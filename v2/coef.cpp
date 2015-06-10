#include <iostream>
#include <cmath>
#include "coef.h"
using namespace std;
double u(double x) {
	double u1, u2;
	u1 = 1.0;
	u2 = 0.25 * u1;
	if (x < 0.0) {
		return u1;
	} else {
		return u2;
	}
}

double kappa(double x, double y) {
	double kappa0 = 5.0;
	return kappa0 * exp(y);
}

double Qinj(double x, double dx, double y, double dy) {
//	cout<<x<<dx<<y<<dy;
	if ((x < 0.1 * dx) && (x > -0.1 * dx) && (y < 0.5 * dy) && (y > -0.5 * dy)) {
//		cout<<"Hello!";
		return 1.0;
	} else {
		return 0.0;
	}
}