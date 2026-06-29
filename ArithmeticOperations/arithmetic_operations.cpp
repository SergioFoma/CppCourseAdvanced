#include <cmath>

#include "arithmetic_operations.hpp"

const double low = 0;
const double high = 100;

double fast_sqrt(const double& X,const double& N){

    if(!( low < X && X < high && low < N && N < high )){
        return -1;
    }

    double epsilon = 1e-9;
    double old_x; 
    double new_x = X < 1.0 ? X : 1.0;
    const double log_X = std::log(X);
    const double div_N = 1.0 / N;
    do{
        old_x = new_x;
        // new_x = (1.0/N) * ((N-1) *  old_x + X / std::pow(old_x, N-1));    -- slowly
        new_x = old_x * div_N * (N * (1 - std::log(old_x)) +  log_X);
    }while(std::fabs(new_x - old_x) >= epsilon * old_x);

    return new_x;
}
