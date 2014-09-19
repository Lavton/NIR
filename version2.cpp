#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <vector>
using namespace std;
typedef vector< double> VecLong;
typedef vector< vector< double> > MatrixVector;
VecLong p;
std::vector<double> u;
std::vector<int> line_numbers;


    int tN;
	double dt;

//p
	double p_min;
	double p_max;
	int pN;
	int corrent_p;
	int p_inj_N;

//x
    std::vector<double> dx_v;
	int xN;
	int corrent_x;
	int x_inj_N;

//u
	int corrent_u;
	double u0;

//common
	int line_number_counter;
	double Q0;
	double D0;


void commonMethods(){
//t
    tN=300;
    dt=0.005;

//x
    xN=500;
    for (int i = 0; i < xN; ++i){
        dx_v.push_back(0.1);
    }
    corrent_x=0;
    x_inj_N = 5;

//p
    pN=500;
    p_min=0.1;
    p_max=1000;
    corrent_p=0;
    p_inj_N = 10;
    p.push_back(p_min);
    for (int i = 1; i < pN; ++i){
        p.push_back(pow(10, log10(p[0])+log10(p_max/p_min)*(i)/pN));
    }
    std::cout<<log10(p[p_inj_N]);

//u
    corrent_u=0;
    u0=4;
    for (int i = 0; i < xN/2; ++i){
        u.push_back(u0);
    }
    for (int i = xN/2; i < xN; ++i){
        u.push_back(u0/4);
    }

//common
    Q0=10;
    D0=2;
    for (int i = 1; i < pN; ++i){
        if (i%3 ==0){
            line_numbers.push_back(i);
        }
    }
    line_number_counter = 0;
}


MatrixVector first_kind_clear(const MatrixVector &f0){
	MatrixVector f1; //(f0.size());
	int xN = f0[0].size();
	VecLong f10;
	for (int i = 0; i < xN; ++i){
		f10.push_back(0);
	}
	f1.push_back(f10);
	int pN = f0.size();
	for (int i = 1; i < pN; ++i){
 		corrent_u = 0;
		double thisP = p[i];
		double dlogP = log10(p[2]/p[1]);
		double dx = dx_v[1];
		VecLong ftmp;
		ftmp.push_back(0);
		for (int j = 1; j < xN-1; ++j){
			double prevU = u[j-1];
			double thisU = u[j];
			double corrent = -(f0[i][j]-f0[i][j-1])/dx+(1/3.0)*((thisU-prevU)/dx) * 
				((f0[i][j]-f0[i-1][j])/dlogP - 4*f0[i][j]) + 
				D0*thisP* (f0[i][j-1] + f0[i][j+1] - 2*f0[i][j])/(dx*dx);

			if ((j == p_inj_N) && (i == x_inj_N)){
				corrent += Q0 * pow(thisP,4);
			}
			ftmp.push_back(corrent);
		}
		ftmp.push_back(0);
		f1.push_back(ftmp);
	}
	return f1;
}
MatrixVector init(){
	MatrixVector v;
	for (int i = 0; i < pN; ++i)
	{

		VecLong v0;
		for (int j = 0; j < xN; ++j){
			v0.push_back(0);
		}
		v.push_back(v0);

	}
	return v;
}


void transp(){
	ifstream inf("f0.txt");
	ofstream outf("Fres.txt");
	commonMethods();
	vector< vector<double> > answer;
	answer.push_back(p);
	MatrixVector f0=init();
	int pN=f0.size();
	for (int i=1; i<tN; i++){
		cout<<"t № "<<i<<endl;
		MatrixVector f1=first_kind_clear(f0);
		swap(f0,f1);
	}

	for (int j = 0; j < pN; ++j){
		if ((j % 50 == 0)){
			answer.push_back(f0[j]);
		}
	}
	for (int i = 0; i < answer[0].size(); i+=10){
		for (int j = 0; j < answer.size(); ++j){
			outf<<answer.at(j).at(i)<<" ";
		}
		outf<<endl;
	}
}



int main(){
	transp();
	return 0;
}
