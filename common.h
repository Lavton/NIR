#ifndef _COMMON_H_
#define _COMMON_H_ 
#include <vector>
typedef std::vector<long double> VecLong;
typedef std::vector< std::vector<long double> > MatrixVector;
class CommonMethods{

//t
public:
    int get_t_numbers() const;
    long double get_next_dt();
private:
    int tN;
	long double dt;

//p
public:
    int get_p_numbers() const;
    long double get_next_dlogp();
    long double get_this_p();
    int get_corrent_p_num() const;
    void clear_corrent_p();
    std::vector<long double> get_all_p() const;
    int get_p_inj_N() const;

private:
	long double p_min;
	long double p_max;
	std::vector<long double> p;
	int pN;
	int corrent_p;
	int p_inj_N;

//x
public:
    int get_x_numbers() const;
    long double get_next_dx();
    int get_corrent_x_num() const;
    void clear_corrent_x();
    std::vector<long double> get_all_x() const;
    int get_x_inj_N() const;
private:
	std::vector<long double> dx;
	int xN;
	int corrent_x;
	int x_inj_N;

//u
public:
    double get_next_u();
    double get_this_u();
    void clear_corrent_u(); 
private:
	std::vector<double> u;
	int corrent_u;
	double u0;

//common
private:        
    CommonMethods();
    CommonMethods(const CommonMethods& root);
    CommonMethods& operator=(const CommonMethods&);
	std::vector<int> line_numbers;
	int line_number_counter;
	double Q0;
	double D0;
public:
	std::vector<double> convect(const VecLong & in);
	double get_Q0() const;
	double get_D0() const;
    int get_last_line_number() const;
    void inc_line_number_counter();
	static std::vector <long double> matrixSolver (const std::vector<long double>& A, 
		const std::vector<long double>& B, const std::vector<long double>& C, 
		const std::vector<long double>& F)
	{
	    int N=A.size();
	    std::vector<long double> alpha(N);
	    std::vector<long double> beta(N);
	    alpha[0]=(B[0]/C[0]);
	    beta[0]=(F[0]/C[0]);
	    for (int i = 1; i < N-1; ++i)   
	    {
	        alpha[i]=(B[i]/(C[i]-alpha.at(i-1)*A[i]));
	        beta[i]=((F[i]-beta.at(i-1)*A[i])/(C[i]-alpha.at(i-1)*A[i]));
	    }
	    std::vector<long double> x(N, 0);
	    x[N-1]=(F[N-1] - A[N-1]*beta[N-2]) / (C[N-1] - A[N-1]*alpha[N-2]);
	    for (int i = N-1; i-- > 0;) {
	        x[i]=beta[i]-alpha[i]*x[i+1];
	    }
	    return x;

	}

	static CommonMethods& Instance(){
	    static CommonMethods theSingleInstance;
	    return theSingleInstance;
	}

};
#endif