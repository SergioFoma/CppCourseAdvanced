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
    
    size_t size = digits.size();
    if (size == 1 && digits[0] == 0) {
        is_positive = true;
    }

    while(size > 1 && digits[size - 1] == 0) {
        digits.pop_back();
        --size;
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

int BigInteger::max_digits_len(){
    int len = 0;
    int copy_base = base;

    while (copy_base > 0) {
        copy_base /= 10;
        ++len;
    }

    return len - 1;
}

int BigInteger::get_base() {
    return base;
}

// Methods
int BigInteger::signum() const {
    return is_positive ? 1 : -1;
}

BigInteger::operator bool() const {
    if (digits.size() == 1 && digits[0] == 0) {
        return false;
    }

    return true;
}
std::string BigInteger::toString() const {
    std::string result{};
    size_t size = digits.size();
    int copy = 0;
    int pow = 0, count = 0;
    if (size == 1 && digits[0] == 0) {
        result.push_back(digits[0] + '0');
        return result;
    }

    for (size_t index = 0; index < size; ++index) {
        copy = digits[index];
        pow = 
            index == size - 1 ? 
                         size :
                         size + 1;

        while (copy > 0) {
            result.push_back(copy % 10 + '0');
            copy /= 10;
            ++count;
        }

        for (int num_ind = 0; num_ind < pow - count; ++num_ind) {
            result.push_back('0');
        }
    }

    if (!is_positive) {
        result.push_back('-');
    }

    std::reverse(result.begin(), result.end());
    return result;
}

void BigInteger::changeSignum() {
    is_positive = !is_positive;
}

BigInteger BigInteger::operator-() const {
    BigInteger other = *this;
    other.changeSignum();
    return other;
}

BigInteger& BigInteger::operator++() {
   int max_num = base - 1;
   int unit = 1;
   size_t size = digits.size();
   size_t index = 0;
   if (!is_positive) {
       is_positive = true;
       --(*this);
       if (!(digits.size() == 1 && digits[0] == 0)) {
           is_positive = false;;
       }
       return *this;
   }

   if (digits[index] < max_num) {
       ++digits[index];
       return *this;
   }
   
    do {
        digits[index] = 0;
        ++index;
        ++digits[index];
    } while (index < size - 1 && digits[index] > max_num);

    if (digits[index] > max_num) {
        digits[index] = 0;
        digits.push_back(unit);
    }
    
   return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger copy = *this;
    ++(*this);
    return copy;
}

BigInteger& BigInteger::operator--() {
    int min_num = 0, max_num = base - 1;
    size_t size = digits.size();
    size_t index = 0;
    if (!is_positive || (size == 1 && digits[0] == 0)) {
        is_positive = true;
        ++(*this);
        is_positive = false;
        return *this;
    }

    if (digits[index] > min_num) {
        --digits[index];
        return *this;
    }
    
    do {
        digits[index] = max_num;
        ++index;
        --digits[index];
    } while (index < size - 1 && digits[index] < min_num);
    

    while (digits[index] == 0) {
        digits.pop_back();
        --index;
    }
    
    return *this; 
}

BigInteger BigInteger::operator--(int) {
    BigInteger copy = *this;
    --(*this);
    return copy;
}

BigInteger& BigInteger::operator+=(const BigInteger& num) {
    if (is_positive != num.is_positive) {
        *this -= -num;
        return *this;
    }
    size_t first_sz = digits.size(), second_sz = num.digits.size();
    size_t min_sz = std::min(first_sz, second_sz);
    int max_num = base - 1;
    int sum = 0;
    size_t index = 0;
    
    for (; index < min_sz; ++index) {
        sum = digits[index] + num.digits[index];
        if (index < min_sz - 1 && sum > max_num) {
            digits[index] = sum % base;
            ++digits[index + 1];
            continue;
        }
        
        digits[index] = sum;
    }
    
    while (first_sz < second_sz && index < second_sz) {
        digits.push_back(num.digits[index]);
        ++index;
        ++first_sz;
    }
    
    index = min_sz - 1;
    while (index < first_sz - 1 && digits[index] > max_num) {
        digits[index] = digits[index] % base;
        ++index;
        ++digits[index];
    }
    
    if (digits[index] > max_num) {
        digits[index] = digits[index] % base;
        digits.push_back(1);
    }
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& num) {
    if (is_positive != num.is_positive) {
        *this += -num;
        return *this;
    }
    size_t first_sz = digits.size(), second_sz = num.digits.size();
    size_t min_sz = std::min(first_sz, second_sz);
    int min_num = 0;
    int delta = 0;
    size_t index = 0;

    *this < num ? is_positive = false : is_positive = true;

    for (; index < min_sz; ++index) {
        delta = digits[index] - num.digits[index];
        if (index < min_sz - 1 && delta < min_num) {
            digits[index] = -delta % base;
            --digits[index + 1];
            continue;
        }
        
        digits[index] = delta;
    }
    
    while (first_sz < second_sz && index < second_sz) {
        digits.push_back(num.digits[index]);
        ++index;
        ++first_sz;
    }
    
    index = min_sz - 1;
    while (index < first_sz && digits[index] < min_num) {
        digits[index] = -digits[index] % base;
        ++index;
        if (index < first_sz) --digits[index];
    }
    
    index = first_sz - 1;
    while (first_sz > 1 && digits[index] == 0){
        digits.pop_back();
        --index;
        --first_sz;
    } 
    return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& num) {
    size_t sz = num.max_digits_len();
    ++sz;
    return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& num) {
    size_t sz = num.max_digits_len();
    ++sz;
    return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& num) {
    size_t sz = num.max_digits_len();
    ++sz;
    return *this;
}

// Functions
bool operator<(const BigInteger& first, const BigInteger& second){
    int first_signum = first.signum(), second_signum = second.signum();
    if (first_signum != second_signum) {
        return first_signum < second_signum ? true : false;
    }
    
    std::string first_str = first.toString(), second_str = second.toString();
    size_t first_sz = first_str.size(), second_sz = second_str.size();
    if (first_sz != second_sz) {
        if (first_signum == -1) return first_sz < second_sz ? false : true;
        return first_sz < second_sz ? true : false;
    }
    
    char first_ch = '0', second_ch = '0';
    size_t index = 0;
    if (first_signum == -1) {
        ++index;
    }
    for (; index < first_sz; ++index) {
        first_ch = first_str[index];
        second_ch = second_str[index];
        if (first_ch == second_ch) continue;

        if (first_signum) return first_ch < second_ch ? false : true;
        return first_ch < second_ch ? true : false;
    }

    return false;
}

bool operator>(const BigInteger& first, const BigInteger& second) {
    return second < first;
}

bool operator<=(const BigInteger& first, const BigInteger& second) {
    return !(first > second);
}

bool operator>=(const BigInteger& first, const BigInteger& second) {
    return !(first < second);
}

bool operator==(const BigInteger& first, const BigInteger& second) {
    int first_signum = first.signum(), second_signum = second.signum();
    if (first_signum != second_signum) return false;

    std::string first_str = first.toString(), second_str = second.toString();
    size_t first_sz = first_str.size(), second_sz = second_str.size();
    if (first_sz != second_sz) return false;

    for (size_t index = 0; index < first_sz; ++index) {
        if (first_str[index] != second_str[index]) return false;
    }

    return true;
}

bool operator!=(const BigInteger& first, const BigInteger& second) {
    return !(first == second);
}

// Destructor
BigInteger::~BigInteger() = default;
