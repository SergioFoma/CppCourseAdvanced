#include <iostream>
#include <limits>

#include "big_integer.hpp"

void dump(const BigInteger& integer);

int main() {
    
    BigInteger int1;
    dump(int1);

    int sz2 = 1'178'234'123;
    BigInteger int2(sz2);
    dump(int2);

    long long sz3 = 178;
    BigInteger int3(sz3);
    dump(int3);

    BigInteger int4("-12345678901234567890");
    dump(int4);

    BigInteger int5("-000");
    dump(int5);


    BigInteger int6("1000000000000000000");
    dump(int6);

    long long num = std::numeric_limits<long long>::min();
    BigInteger int7(num);
    dump(int7);
}

void dump(const BigInteger& integer) {
   
    std::cout << "is positive = " << integer.get_sign() << '\n'; 
    std::cout << "base = " << integer.get_base() << '\n';

    const std::vector<int>& digits = integer.get_digits();
    size_t size = digits.size();
    for (size_t index = 0; index < size; ++index) {
        std::cout << digits[index] << ' ';
    }
    std::cout << "\n\n";
}
