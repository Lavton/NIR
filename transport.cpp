#include "transport.h"

using namespace std;
MatrixVector first_kind(const MatrixVector &f0, long double p){
	MatrixVector f1;
/*	f1.push_back(0);
	CommonMethods::Instance().clear_corrent_x();
	int xN=f0.size();
	for (int i=1; i<xN-1; i++){
		long double dx = CommonMethods::Instance().get_next_dx();
		long double dt = CommonMethods::Instance().get_next_dt();

		long double df=f0[i-1]+f0[i+1]-2*f0[i];
//		cerr<<dx<<" "<<df<<endl;

		df *=p/(dx*dx);
		f1.push_back(df*dt+f0[i]);		
	}
	f1.push_back(0);*/
	return f1;
}
