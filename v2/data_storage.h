#ifndef _DATA_STORAGE_H_
#define _DATA_STORAGE_H_

class DataStorage {
public:
	long double **alpha;
	long double **beta;
	long double **A;
	long double **C;
	long double **B;
	long double **F;
	long double **Xg;
	static DataStorage& Instance(int Nx, int tn) {
		static DataStorage theSingleInstance(Nx, tn);
		return theSingleInstance;
	}

private:
	DataStorage(int Nx, int tn) {
		alpha = new long double*[tn];
		beta = new long double*[tn];
		A = new long double*[tn];
		C = new long double*[tn];
		B = new long double*[tn];
		F = new long double*[tn];
		Xg = new long double*[tn];

		for (int i = 0; i < tn; i++) {
			alpha[i] = new long double[Nx + 1];
			beta[i] = new long double[Nx + 1];
			A[i] = new long double[Nx];
			C[i] = new long double[Nx + 1];
			B[i] = new long double[Nx];
			F[i] = new long double[Nx + 1];
			Xg[i] = new long double[Nx + 1];
		}
	}
};

#endif