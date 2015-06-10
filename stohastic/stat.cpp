#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <climits>
#include <cfloat>
#include "stat.h"

using namespace std;
unsigned int g_rnd_seed = 1;

void set_g_rnd_seed(unsigned int seed) {
	g_rnd_seed = seed ? seed : 1;
}

inline double sqr(double v) {
	return v * v;
}

double sigma(double *x, int n) {
	if (n < 2) {
		return 0;
	}
	double av = 0;
	double di = 0;
	for (int i = 0; i < n; i++) {
		av += x[i];
		di += x[i] * x[i];
	}

	av /= n;
	di /= n;
	di -= av * av;
	di *= n * 1.0 / (n - 1);
	return di > 0 ? sqrt(di) : 0;
}

double max_arr(double *x, int n) {
	double maxim = DBL_MIN;
	for (int i = 0; i < n; i++) {
		if (maxim <= x[i]) {
			maxim = x[i];
		}
	}
	return maxim;
}

double min_arr(double *x, int n) {
	double minim = DBL_MAX;
	for (int i = 0; i < n; i++) {
		if (minim >= x[i]) {
			minim = x[i];
		}
	}
	return minim;
}

inline unsigned int rnd_i() {
	return g_rnd_seed = (16807L * g_rnd_seed) % 2147483647L;
}

inline unsigned int rnd_u() {
	return g_rnd_seed = g_rnd_seed * 1664525L + 1013904223L;
}

inline double rnd() {
	return double(rnd_u()) / UINT_MAX;
}

double rnd_g() {
	static int was = 0;
	static double r = 0;
	if (was) {
		was = 0;
		return r;
	}
	double s, v1, v2;
	do {
		v1 = 2 * rnd() - 1;
		v2 = 2 * rnd() - 1;
		s = v1 * v1 + v2 * v2;
	} while (s >= 1.0 || s == 0);

	was = 1;
	r = v1 * sqrt(-2 * log(s) / s);
	return v2 * sqrt(-2 * log(s) / s);
}
