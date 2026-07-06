#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>

#include "big_integer.hpp"

// Constructors
BigInteger::BigInteger(): is_positive(true) {
    digits.push_back(0);
}

BigInteger::BigInteger(long long num): is_positive(num >= 0) {
    if (num == std::numeric_limits<long long>::min()) {
        unsigned long long un_num = static_cast<unsigned long long>(num);       // -2^32 + 2^64 = 2^32 - correct positive num
        std::cout << "un_num = " << un_num << '\n';
        convert_system(un_num);
    }
    else {
        convert_system(std::abs(num)); 
    }
}

BigInteger::BigInteger(int num): BigInteger(static_cast<long long>(num)) {}

BigInteger::BigInteger(const std::string& str) {
    int digits_size = this->max_digits_len();
    int str_size = static_cast<int>(str.size());
    int lower_bound = 0;
    int start;

    if (str[0] == '+') {
        ++lower_bound;
        is_positive = true;
    }
    else if (str[0] == '-') {
        ++lower_bound;
        is_positive = false;
    }
    
    std::string one_digit;
    for (int str_index = str_size - 1; str_index >= lower_bound; str_index -= digits_size) {
        start = str_index - digits_size + 1;
        if (start < lower_bound) start = lower_bound;
        for (int dig_index = start; dig_index <= str_index; ++dig_index) {
            one_digit.push_back(str[dig_index]);
        }
        digits.push_back(std::stoi(one_digit));
        one_digit.clear();
    }
    
    if (digits.size() == 1 && digits[0] == 0) {
        is_positive = true;
    }
}

// Local functions
void BigInteger::convert_system(unsigned long long num) {
    if (num == 0) {
        digits.push_back(num);
        return ;
    }

    while (num > 0) {
        digits.push_back(num % base);
        num /= base;
    }
}

int BigInteger::max_digits_len() const {
    int len = 0;
    int copy_base = base;

    while (copy_base > 0) {
        copy_base /= 10;
        ++len;
    }

    return len - 1;
}

// Methods
const std::vector<int>& BigInteger::get_digits() const {
    return this->digits;
}

int BigInteger::get_base() const {
    return base;
}

bool BigInteger::get_sign() const {
    return is_positive;
}

// Destructor
BigInteger::~BigInteger() = default;
