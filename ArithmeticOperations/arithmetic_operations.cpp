#include <cmath>

#include "arithmetic_operations.hpp"

double fast_sqrt(double X, double N){
    double epsilon = 1e-9;
    double old_x; 
    double new_x = X / N;
    do{
        old_x = new_x;
        // new_x = (1.0/N) * ((N-1) *  old_x + X / std::pow(old_x, N-1));    -- slowly
        new_x = (old_x / N) * (N * (1 - std::log(old_x)) +  std::log(X));
    }while(std::fabs(new_x - old_x) >= epsilon);

    return new_x;
}
