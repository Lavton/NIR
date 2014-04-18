#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include "common.h"
#include "diffusion.h"
#include "transport.h"
using namespace std;

void diffus(){
	ifstream inf("f0.txt");
	ofstream outf("Fres.txt");
	std::vector< std::vector<double> > answer;
	answer.push_back(CommonMethods::Instance().convect(CommonMethods::Instance().get_all_x()));
	long double p=1;
	std::vector<long double> f0=init1();
	answer.push_back(CommonMethods::Instance().convect(f0));
	int xN=f0.size();
	int tN=CommonMethods::Instance().get_t_numbers();

	for (int i=1; i<tN; i++){
		cout<<"t= "<<i*CommonMethods::Instance().get_next_dt()<<endl;
		std::vector<long double> f1 = first_kind(f0, p);
		if(i==CommonMethods::Instance().get_last_line_number()){
			cerr<<CommonMethods::Instance().get_last_line_number()<<endl;
			answer.push_back(CommonMethods::Instance().convect(f1));
			CommonMethods::Instance().inc_line_number_counter();
		}
		swap(f0,f1);
	}

	for (int i = 0; i < answer[0].size(); ++i){
		for (int j = 0; j < answer.size(); ++j){
			outf<<answer.at(j).at(i)<<" ";
		}
		outf<<endl;
	}
}

void transp(){
	ifstream inf("f0.txt");
	ofstream outf("Fres.txt");
	std::vector< std::vector<double> > answer;
	answer.push_back(CommonMethods::Instance().convect(CommonMethods::Instance().get_all_x()));
	long double p=1;
	MatrixVector f0=init();
		int pN=f0.size();
	int tN=CommonMethods::Instance().get_t_numbers();
	for (int i=1; i<tN; i++){
		MatrixVector f1=first_kind_nonclear(f0);
		swap(f0,f1);
	}
	for (int j = 0; j < pN; ++j){
		if (j == CommonMethods::Instance().get_last_line_number()){
			answer.push_back(CommonMethods::Instance().convect(f0[j]));
			CommonMethods::Instance().inc_line_number_counter();
		}
	}
	for (int i = 0; i < answer[0].size(); ++i){
		for (int j = 0; j < answer.size(); ++j){
			outf<<answer.at(j).at(i)<<" ";
		}
		outf<<endl;
	}
}
int main(){
//	diffus();
	transp();
	return 0;
}





//транспортное уравнение
//стохастическое уроавнение и сравнение с разностным