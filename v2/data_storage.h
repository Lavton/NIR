#ifndef _DATA_STORAGE_H_
#define _DATA_STORAGE_H_

class DataStorage {
public:
	double **alpha;
	double **beta;
	double **A;
	double **C;
	double **B;
	double **F;
	double **Xg;
	static DataStorage& Instance(int Nx, int tn){
	    static DataStorage theSingleInstance(Nx, tn);
	    return theSingleInstance;
	}

private:
	DataStorage(int Nx, int tn) {
		alpha = new double*[tn];
		beta = new double*[tn];
		A = new double*[tn];
		C = new double*[tn];
		B = new double*[tn];
		F = new double*[tn];
		Xg = new double*[tn];

		for (int i = 0; i < tn; i++){
			alpha[i] = new double[Nx + 1];
			beta[i] = new double[Nx + 1];
			A[i] = new double[Nx];
			C[i] = new double[Nx + 1];
			B[i] = new double[Nx];
			F[i] = new double[Nx + 1];
			Xg[i] = new double[Nx + 1];
		}
	}
};

#endif