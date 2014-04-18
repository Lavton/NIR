#include <vector>
#include "common.h"
#include <cmath>
#include <iostream>
CommonMethods::CommonMethods(){
//t
    tN=10000;
    dt=0.005;

//x
    xN=900;
    for (int i = 0; i < xN; ++i){
        dx.push_back(0.1);
    }
    corrent_x=0;
    x_inj_N = 50;

//p
    pN=900;
    p_min=0.01;
    p_max=1000;
    corrent_p=0;
    p_inj_N = 100;
    p.push_back(p_min);
    for (int i = 1; i < pN; ++i){
        p.push_back(pow(10, log10(p[0])+log10(p_max/p_min)*(i)/pN));
    }

//u
    corrent_u=0;
    u0=50;
    for (int i = 0; i < xN/2; ++i){
        u.push_back(u0);
    }
    for (int i = xN/2; i < xN; ++i){
        u.push_back(u0/2);
    }

//common
    Q0=10;
    D0=2;
    for (int i = 1; i < tN; ++i){
        if (i%50 ==0){
            line_numbers.push_back(i);
        }
    }
    line_number_counter = 0;
}

//t
    int CommonMethods::get_t_numbers() const{
        return tN;
    }
    long double CommonMethods::get_next_dt(){
        return dt;
    }


//x
    int CommonMethods::get_x_numbers() const{
        return xN;
    }
    long double CommonMethods::get_next_dx(){
        if (corrent_x >= xN){
            corrent_x=0;
        }
        ++corrent_x;
        long double res = dx[corrent_x];
        return res;
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
    int CommonMethods::get_x_inj_N() const{
        return x_inj_N;
    }

//p
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
    long double CommonMethods::get_next_dlogp(){
        long double res;
        if (corrent_p == 0)
        {
            res = log10(p[1]/p[0]);
            corrent_p++;
        }else{
            ++corrent_p;
            if (corrent_p >= pN){
                corrent_p=0;
            }
            res = log10(p[corrent_p]/p[corrent_p-1]);
        }
        return res;
    }

    long double CommonMethods::get_this_p() {
        return p[corrent_p];
    }

    int CommonMethods::get_p_inj_N() const{
        return p_inj_N;
    }

//u
    double CommonMethods::get_next_u(){
        ++corrent_u;
        if (corrent_u >= xN){
            corrent_u=0;
        }
        return u[corrent_u];

    }
    double CommonMethods::get_this_u(){
        return u[corrent_u];
    }
    void CommonMethods::clear_corrent_u(){
        corrent_u = 0;
    }


//common
    double CommonMethods::get_Q0() const{
        return Q0;
    }
    double CommonMethods::get_D0() const{
        return D0;
    }
    int CommonMethods::get_last_line_number() const{
        return line_numbers[line_number_counter];
    }
    void CommonMethods::inc_line_number_counter(){
        if(!(line_number_counter==line_numbers.size()-1)){
            line_number_counter++;
        }
    }
    std::vector<double> CommonMethods::convect(const VecLong & in){
        std::vector<double> v(in.size());
        for (int i = 0; i < in.size(); ++i)
        {
            v[i] = (double) in[i];
        }
        return v;
    }
