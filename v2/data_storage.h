#ifndef _DATA_STORAGE_H_
#define _DATA_STORAGE_H_

class DataStorage {
public:
	double *alpha;
	double *beta;
	double *A;
	double *C;
	double *B;
	double *F;
	double *Xg;
	static DataStorage& Instance(int Nx){
	    static DataStorage theSingleInstance(Nx);
	    return theSingleInstance;
	}

private:
	DataStorage(int Nx) {
		alpha = new double[Nx + 1];
		beta = new double[Nx + 1];
		A = new double[Nx];
		C = new double[Nx + 1];
		B = new double[Nx];
		F = new double[Nx + 1];
		Xg = new double[Nx + 1];
	}
};

#endif