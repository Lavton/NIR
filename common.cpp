#include <vector>
#include "common.h"
#include <iostream>
CommonMethods::CommonMethods(){
    tN=10000;
//    dx=0.1;
    dt=0.005;
    xN=900;
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

