#include <iostream>
#include <cmath>
#include "coef.h"
using namespace std;
long double u(long double x) {
	long double V0 = 1;/* 5000.0 * 1000 * 100;*/
	long double u1, u2;
	u1 = 1.0;
	u2 = 0.25 * u1;
	if (x < 0.0) {
		return u1*V0;
	} else {
		return u2*V0;
	}
}

long double kappa(long double x, long double y) {
	long double k0 = 1; /*3*pow(10, 27);*/
	long double kappa0 = 0.6*k0;
	return kappa0 * exp(y);
}

long double Qinj(long double x, long double dx, long double y, long double dy) {
	long double t0 = 3.0 * pow(10, 7);
//	cout<<x<<dx<<y<<dy;
	if ((x < 0.1 * dx) && (x > -0.1 * dx) && (y < 0.5 * dy) && (y > -0.5 * dy)) {
//		cout<<"Hello!";
		return 3.0;
	} else {
		return 0.0;
	}
}