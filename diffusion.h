#ifndef DIFFUSION_H_
#define DIFFUSION_H_
#include "common.h"
#include <vector>

std::vector<long double> first_kind(const std::vector<long double> &f0, long double p);
std::vector<long double> second_kind(const std::vector<long double> &f0, long double p);
std::vector<long double> first_kind_nonclear(const std::vector<long double> &f0, long double p);
std::vector<long double> init();
#endif