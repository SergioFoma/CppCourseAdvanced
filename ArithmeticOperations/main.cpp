#include <iostream>

#include "arithmetic_operations.hpp"

int main(){

    double N;   
    std::cout << "N: ";
    std::cin >> N;

    double X;
    std::cout << "X: ";
    std::cin >> X;
    
    
    std::cout << "result = " << fast_sqrt(X, N) << '\n';
}
