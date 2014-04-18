#ifndef _TRANSPORT_H_
#define _TRANSPORT_H_
#include "common.h"
#include <vector>

MatrixVector first_kind(const MatrixVector &f0, long double p);
MatrixVector second_kind(const MatrixVector &f0, long double p);
MatrixVector first_kind_nonclear(const MatrixVector &f0);
MatrixVector init();





#endif