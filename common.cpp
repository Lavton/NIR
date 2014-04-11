#include <vector>
#include "common.h"
#include <cmath>
#include <iostream>
CommonMethods::CommonMethods(){
    tN=10000;
//    dx=0.1;
    dt=0.005;
    xN=900;
    pN=900;
    p_min=0.01;
    p_max=1000;
    for (int i = 1; i < tN; ++i){
        if (i%50 ==0){
            line_numbers.push_back(i);
        }
    }
    line_number_counter = 0;

    for (int i = 0; i < xN; ++i){
        dx.push_back(0.1);
    }
    corrent_x=0;
    corrent_p=0;
    p.push_back(p_min);
    for (int i = 1; i < pN; ++i)
    {
        p.push_back(pow(10, p[0]+log10(p_max/p_min)*(i)/pN));
    }
}
int CommonMethods::get_t_numbers() const{
    return tN;
}
int CommonMethods::get_x_numbers() const{
    return xN;
}
long double CommonMethods::get_next_dx(){
    long double res = dx[corrent_x = corrent_x++];
    if (corrent_x >= xN){
        corrent_x=0;
    }
    return res;
}
long double CommonMethods::get_next_dt(){
    return dt;
}
int CommonMethods::get_corrent_x_num() const{
    return corrent_x;
}
void CommonMethods::clear_corrent_x(){
    corrent_x=0;
}
std::vector<long double> CommonMethods::get_all_x() const{
    std::vector<long double> v;
    v.push_back(dx[0]);
    for (int i = 1; i < xN; ++i){
        v.push_back(v[i-1]+dx[i]);
    }
    return v;
}
int CommonMethods::get_last_line_number() const{
    return line_numbers[line_number_counter];
}
void CommonMethods::inc_line_number_counter(){
    if(!(line_number_counter==line_numbers.size()-1)){
        line_number_counter++;
    }
}





int CommonMethods::get_corrent_p_num() const{
    return corrent_p;
}
void CommonMethods::clear_corrent_p(){
    corrent_p=0;
}
std::vector<long double> CommonMethods::get_all_p() const{
    std::vector<long double> v;
    v.push_back(p[0]);
    for (int i = 1; i < pN; ++i){
        v.push_back(p[i]);
    }
    return v;
}
int CommonMethods::get_p_numbers() const{
    return pN;
}
long double CommonMethods::get_next_dp(){
    long double res;
    if (corrent_p == 0)
    {
        res = (p[1]-p[0])/2;
        corrent_p++;
    }else{
        res = -p[corrent_p]+p[++corrent_p];
    }
    if (corrent_p >= pN){
        corrent_p=0;
    }
    return res;
}

long double CommonMethods::get_this_p() {
    return p[corrent_p];
}