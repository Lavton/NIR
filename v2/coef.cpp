#include <iostream>
#include <cmath>
#include "coef.h"
using namespace std;
long double u(long double x) {
	long double u1, u2;
	u1 = 1.0;
	u2 = 0.25 * u1;
	if (x < 0.0) {
		return u1;
	} else {
		return u2;
	}
}

long double kappa(long double x, long double y) {
	long double kappa0 = 1;
	return kappa0 * exp(y);
}

long double Qinj(long double x, long double dx, long double y, long double dy) {
//	cout<<x<<dx<<y<<dy;
	if ((x < 0.1 * dx) && (x > -0.1 * dx) && (y < 0.5 * dy) && (y > -0.5 * dy)) {
//		cout<<"Hello!";
		return 5.0;
	} else {
		return 0.0;
	}
}