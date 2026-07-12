#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>
#include <utility>

#include "big_integer.hpp"

// Constructors
BigInteger::BigInteger(): is_positive(true) {
    digits.push_back(0);
}

BigInteger::BigInteger(long long num): is_positive(num >= 0) {
    if (num == std::numeric_limits<long long>::min()) {
        unsigned long long un_num = -static_cast<unsigned long long>(num);       // 2^64 - (-2^63 + 2^64) = 2^63 - correct positive num
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

BigInteger::BigInteger(const BigInteger& num) = default;

BigInteger& BigInteger::operator=(BigInteger num) & {
    this->swap(num);
    return *this;
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

void BigInteger::knuth_div(const BigInteger& divider, BigInteger& quotient, BigInteger& remainder) {
    BigInteger copy = divider;
    copy.is_positive = true;
    
    size_t sz = digits.size(), copy_sz = copy.digits.size();
    int n = copy_sz, m = sz - n;
    
    if (copy_sz == 1 && copy.digits[0] == 0) return;                // zero division;
    if (*this == copy) {
        quotient.digits[0] = 1;
        return ;
    }
    if (m < 0 || (m == 0 && *this < copy)) {
        std::swap(digits, remainder.digits);
        return ;
    }

    std::reverse(digits.begin(), digits.end());
    std::reverse(copy.digits.begin(), copy.digits.end());
 
    if (n == 1) {
        std::vector<int>& q_digits = quotient.digits;
        std::vector<int>& r_digits = remainder.digits;
        r_digits.clear();
        q_digits.clear();
        unsigned long long r = 0, current = 0, digit = 0; 
        for (size_t index = 0; index < sz; ++index) {
            digit = static_cast<unsigned long long>(digits[index]);
            current = r * base + digit;
            q_digits.push_back(current / copy.digits[0]);
            r = current % copy.digits[0];
        }

        size_t q_sz = q_digits.size();
        while (q_sz > 1 && q_digits[0] == 0) {
            q_digits.erase(q_digits.begin());
        }
        r_digits.push_back(r);
        std::reverse(digits.begin(), digits.end());
        return ;
    }

    unsigned long long d = base / (copy.digits[0] + 1);
    BigInteger u, v;
    u.multiply_by_digit(*this, d);
    v.multiply_by_digit(copy, d);

    if (static_cast<int>(u.digits.size()) == m + n) {
        u.digits.insert(u.digits.begin(), 0);
    }
    
    std::vector<int>& q_ans = quotient.digits;
    std::vector<int>& r_ans = remainder.digits;
    r_ans.clear();
    q_ans.resize(m + 1);
    std::fill(q_ans.begin(), q_ans.end(), 0);
    
    this->create_quotient(u, v, q_ans);
    this->denormalization_remainder(u, r_ans, n, d);

    size_t q_sz = q_ans.size(), r_sz = r_ans.size();

    while (q_sz > 1 && q_ans[0] == 0) {
        q_ans.erase(q_ans.begin());
        --q_sz;
    }
    while (r_sz > 1 && r_ans[0] == 0) {
        r_ans.erase(r_ans.begin());
        --r_sz;
    }

    std::reverse(q_ans.begin(), q_ans.end());
    std::reverse(r_ans.begin(), r_ans.end());
}

void BigInteger::multiply_by_digit(BigInteger& num, unsigned long long divider) {
    unsigned long long carry = 0, cur = 0, digit = 0;
    std::vector<int>& num_digits = num.digits;
    std::vector<int>& res = this->digits;
    res.clear();
    int sz = num_digits.size();
    for (int index = sz - 1; index > -1; --index) {
        digit = static_cast<unsigned long long>(num_digits[index]);
        cur = digit * divider + carry;
        res.push_back(cur % base);
        carry = cur / base;
    }
    if (carry > 0) {
        res.push_back(carry);
    }
    std::reverse(res.begin(), res.end());
}

void BigInteger::create_quotient(BigInteger& u_num, BigInteger& v_num, std::vector<int>& q_ans) {
    std::vector<int>& u = u_num.digits;
    std::vector<int>& v = v_num.digits;
    size_t m = q_ans.size() - 1, n = v.size();
    for(size_t j = 0; j <= m; ++j) {
        unsigned long long u_j = u[j], u_j1 = u[j + 1];
        unsigned long long u_j2 = 
                                    j + 2 < u.size() ?
                                             u[j + 2]:
                                                    0;
        unsigned long long v1 = v[0];
        unsigned long long v2 =
                                 v.size() > 1 ?
                                         v[1] :
                                            0 ;
        unsigned long long q_hat = (u_j * base + u_j1) / v1;
        unsigned long long r_hat = (u_j * base + u_j1) % v1;
        while (q_hat == base || q_hat * v2 > r_hat * base + u_j2) {
            q_hat -= 1;
            r_hat += v1;
            if (r_hat >= base) break;
        }
        std::vector<int> current_window(u.begin() + j, u.begin() + j + n + 1);
        BigInteger v_mul_num;
        v_mul_num.multiply_by_digit(v_num, q_hat);
        std::vector<int>& v_mul = v_mul_num.digits;
        if (v_mul.size() < n + 1) {
            v_mul.insert(v_mul.begin(), n + 1 - v_mul.size(), 0);
        }
        int borrow = 0, diff = 0;
        std::vector<int> sub_res(n + 1);
        for (int i = n; i > -1; --i) {
            diff = current_window[i] - v_mul[i] - borrow;
            if (diff < 0) {
                diff += base;
                borrow = 1;
            }
            else borrow = 0;
            sub_res[i] = diff;
        }
        
        for (size_t index = j; index < j + n + 1; ++index) {
            u[index] = sub_res[index - j];
        }

        if (borrow > 0) {
            q_hat -= 1;
            int carry = 0, v_digit = 0, sm = 0;
            for (int i = n; i > -1; --i) {
                i > 0 ?
                    v_digit = v[i - 1] :
                    v_digit = 0;
                sm = u[j + i] + v_digit + carry;
                u[j + i] = sm % base;
                carry = sm / base;
            } 
        }

        q_ans[j] = q_hat;
    }
}

void BigInteger::denormalization_remainder(BigInteger& u_num, std::vector<int>& r_ans, size_t n, unsigned long long d) {
    std::vector<int>& u = u_num.digits;

    if (u.size() < n) {
        r_ans.push_back(0);
        return ;
    }

    std::vector<int> rem_normalized(n);
    size_t start_index = u.size() - n;
    for (size_t i = 0; i < n; ++i) {
        rem_normalized[i] = u[start_index + i];
    }
    unsigned long long rem_carry = 0, current = 0;
    for (size_t index = 0; index < rem_normalized.size(); ++index) {
        current = rem_carry * base + rem_normalized[index];
        r_ans.push_back(static_cast<int>(current / d));
        rem_carry = current % d;
    }
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
    int size = static_cast<int>(digits.size());
    const int base_len = this->max_digits_len();
    int copy = 0;
    int pow = 0, count = 0, upper_bound = 0;
    if (size == 1 && digits[0] == 0) {
        result.push_back(digits[0] + '0');
        return result;
    }

    for (int index = 0; index < size; ++index) {
        copy = digits[index];
        pow = index * base_len;
        upper_bound = pow - count;
        for (int num_ind = 0; num_ind < upper_bound; ++num_ind) {
            result.push_back('0');
            ++count;
        }
        
        while (copy > 0) {
            result.push_back(copy % 10 + '0');
            copy /= 10;
            ++count;
        }
    }

    if (!is_positive) {
        result.push_back('-');
    }

    std::reverse(result.begin(), result.end());
    return result;
}

void BigInteger::changeSignum() {
    if (*this != 0) is_positive = !is_positive;
}

void BigInteger::swap(BigInteger& num) {
    std::swap(digits, num.digits);
    std::swap(is_positive, num.is_positive);
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
        if (index == size) digits.push_back(unit);
        else               ++digits[index];
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
    
    index = size - 1;
    while (size > 1 && digits[index] == 0) {
        digits.pop_back();
        --index;
        --size;
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
        ++first_sz;
    }

    index = first_sz - 1;
    while (first_sz > 1 && digits[index] == 0) {
        digits.pop_back();
        --index;
        --first_sz; 
    }
    
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& num) {
    if (is_positive != num.is_positive) {
        *this += -num;
        return *this;
    } 
    *this < num ? is_positive = false : is_positive = true;
    bool old_is_positive = is_positive;

    BigInteger copy_num = num;
    copy_num.is_positive = true;
    is_positive = true;

    if (*this < copy_num) std::swap(digits, copy_num.digits);
    is_positive = old_is_positive;

    size_t first_sz = digits.size(), second_sz = copy_num.digits.size();
    size_t min_sz = std::min(first_sz, second_sz);
    int min_num = 0;
    int delta = 0;
    size_t index = 0;


    for (; index < min_sz; ++index) {
        delta = digits[index] - copy_num.digits[index];
        if (index < min_sz + 1 && delta < min_num) {
            digits[index] = (delta + base) % base;
            --digits[index + 1];
            continue;
        }
        
        digits[index] = delta;
    }
    
    index = min_sz - 1;
    while (index < first_sz && digits[index] < min_num) {
        digits[index] = (digits[index] + base) % base;
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
    is_positive == num.is_positive ? 
                is_positive = true : 
                is_positive = false;
    
    bool old_positive = is_positive;
    BigInteger copy_num = num;
    copy_num.is_positive = true;
    is_positive = true;
    if (*this < copy_num) std::swap(digits, copy_num.digits);
    is_positive = old_positive;

    std::reverse(digits.begin(), digits.end());
    std::reverse(copy_num.digits.begin(), copy_num.digits.end());

    BigInteger sum_res;
    int first_sz = digits.size(), second_sz = copy_num.digits.size(), count = 0;
    unsigned long long mul = 0, div = 0, mod = 0;
    unsigned long long copy_first = 0, copy_second = 0;
    for(int second_index = second_sz - 1; second_index > -1; --second_index) {
        BigInteger mul_res;
        mul_res.digits.pop_back();
        count = second_index;
        while (count < second_sz - 1) {
            mul_res.digits.push_back(0);
            ++count;
        }
        div = 0;
        for (int first_index = first_sz - 1; first_index > -1; --first_index) {
                copy_first = static_cast<unsigned long long>(digits[first_index]);
                copy_second = static_cast<unsigned long long>(copy_num.digits[second_index]);
                mul = copy_first * copy_second;
                mul += div;
                div = mul / base;
                mod = mul % base;
                mul_res.digits.push_back(mod);
        }
        if (div) mul_res.digits.push_back(div);
        sum_res += mul_res;
    }
    
    digits = std::move(sum_res.digits);
    return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& num) {
    is_positive == num.is_positive ? 
                is_positive = true : 
                is_positive = false;
    bool old_positive = is_positive;

    is_positive = true;                                      // algorithm for positive numbers
    BigInteger quotient, remainder;

    this->knuth_div(num, quotient, remainder);
    is_positive = old_positive; 
    digits = std::move(quotient.digits);
    return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& num) {
    bool old_positive = is_positive;

    is_positive = true;                                      // algorithm for positive numbers
    BigInteger quotient, remainder;

    this->knuth_div(num, quotient, remainder);
    if (remainder.digits.size() == 1 && remainder.digits[0] == 0) is_positive = true;
    else is_positive = old_positive;
    digits = std::move(remainder.digits);
    return *this;
}

// Functions
bool operator<(const BigInteger& first, const BigInteger& second){
    int first_signum = first.signum(), second_signum = second.signum();
    if (first_signum != second_signum) {
        return first_signum < second_signum ? true : false;
    }
    
    const std::vector<int>& first_digits = first.digits;
    const std::vector<int>& second_digits = second.digits;
    size_t first_sz = first_digits.size(), second_sz = second_digits.size();
    if (first_sz != second_sz) {
        if (first_signum == -1) return first_sz < second_sz ? false : true;
        return first_sz < second_sz ? true : false;
    }
    
    size_t index = 0;
    for (size_t upper_bound = first_sz; upper_bound > 0; --upper_bound) {
        index = upper_bound - 1;
        if (first_digits[index] == second_digits[index]) continue;

        if (first_signum == 1) {
            return first_digits[index] < second_digits[index] ? true : false;
        }

        return first_digits[index] < second_digits[index] ? false : true;
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
    
    return first.digits == second.digits;
}

bool operator!=(const BigInteger& first, const BigInteger& second) {
    return !(first == second);
}

BigInteger operator+(const BigInteger& first, const BigInteger& second) {
    BigInteger copy = first;
    copy += second;
    return copy;
}

BigInteger operator-(const BigInteger& first, const BigInteger& second) {
    BigInteger copy = first;
    copy -= second;
    return copy;
}

BigInteger operator*(const BigInteger& first, const BigInteger& second) {
    BigInteger copy = first;
    copy *= second;
    return copy;
}

BigInteger operator/(const BigInteger& first, const BigInteger& second) {
    BigInteger copy = first;
    copy /= second;
    return copy;
}

BigInteger operator%(const BigInteger& first, const BigInteger& second) {
    BigInteger copy = first;
    copy %= second;
    return copy;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& num) {
    out << num.toString();
    return out;
}

std::istream& operator>>(std::istream& in, BigInteger& num) {
    std::string str;

    if (in >> str) {
        num = BigInteger(str);
    }

    return in; 
}

// Destructor
BigInteger::~BigInteger() = default;
