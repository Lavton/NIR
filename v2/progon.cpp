#include "progon.h"
#include "data_storage.h"
void matrix_solver(double *A, double *C, double *B, int N, double *F, double *x, double *alpha, double *beta) {
    alpha[1] = -(B[1] / C[1]);
    beta[1] = (F[1] / C[1]);
    for (int i = 2; i <= N; ++i) {
        alpha[i] = (-B[i] / (C[i] + alpha[i - 1] * A[i - 1]));
        beta[i] = ((F[i] - beta[i - 1] * A[i - 1]) / (C[i] +
                   alpha[i - 1] * A[i - 1]));
    }
    x[N + 1] = ((F[N + 1] - beta[N] * A[N]) / (C[N + 1] +
                alpha[N] * A[N]));
    for (int i = 1; i <= N; i++) {
        x[N + 1 - i] = alpha[N - i + 1] * x[N - i + 2] + beta[N - i + 1];
    }
}