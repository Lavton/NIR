#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include "common.h"
#include "diffusion.h"
using namespace std;

int main(){
	ifstream inf("f0.txt");
	ofstream outf("Fres.txt");
	std::vector< std::vector<long double> > answer;
	answer.push_back(CommonMethods::Instance().get_all_x());
	long double p=1;
	std::vector<long double> f0=init();
	answer.push_back(f0);
	int xN=f0.size();
	int tN=CommonMethods::Instance().get_t_numbers();

	for (int i=1; i<tN; i++){
		cout<<"t= "<<i*CommonMethods::Instance().get_next_dt()<<endl;
		std::vector<long double> f1 = first_kind(f0, p);
		if(i==CommonMethods::Instance().get_last_line_number()){
			cerr<<CommonMethods::Instance().get_last_line_number()<<endl;
			answer.push_back(f1);
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


	return 0;
}





//транспортное уравнение
//стохастическое уроавнение и сравнение с разностным