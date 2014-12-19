#ifndef _STAT_H_
#define _STAT_H_
using namespace std;

void set_g_rnd_seed(unsigned int seed);

double sigma(double *x, int n);

double max_arr(double *x, int n);

double min_arr(double *x, int n);

inline unsigned int rnd_i();

inline unsigned int rnd_u();

inline double rnd();

double rnd_g();
#endif