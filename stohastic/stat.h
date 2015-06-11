#ifndef _STAT_H_
#define _STAT_H_
using namespace std;

void set_g_rnd_seed(unsigned int seed);
long double sigma(long double *x, int n);
long double max_arr(long double *x, int n);
long double min_arr(long double *x, int n);
inline unsigned int rnd_i();
inline unsigned int rnd_u();
inline long double rnd();
long double rnd_g();
#endif