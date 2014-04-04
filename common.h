#ifndef _COMMON_H_
#define _COMMON_H_ 
#include <vector>
class CommonMethods{
public:
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
    int get_t_numbers() const;
    int get_x_numbers() const;
    long double get_next_dx();
    long double get_next_dt();
    int get_corrent_x_num() const;
    void clear_corrent_x();
    std::vector<long double> get_all_x() const;
    int get_last_line_number() const;
    void inc_line_number_counter();
private:        
    CommonMethods();
    CommonMethods(const CommonMethods& root);
    CommonMethods& operator=(const CommonMethods&);
    int tN;
	long double dt;
	std::vector<long double> dx;
	int xN;
	int corrent_x;
	std::vector<int> line_numbers;
	int line_number_counter;
};
#endif