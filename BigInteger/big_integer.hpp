#ifndef BIG_INTEGER_HPP
#define BIG_INTEGER_HPP

#include <vector>
#include <string>
#include <ostream>
#include <istream>

class BigInteger {
private:
    std::vector<int> digits;
    static constexpr int base = 1e9;
    bool is_positive = true;
    void convert_system(unsigned long long num);
    static int max_digits_len();
    static int get_base();
    void knuth_div(const BigInteger& divider, BigInteger& quotient, BigInteger& remainder);
    void multiply_by_digit(BigInteger& num, unsigned long long divider);
    void create_quotient(BigInteger& u_num, BigInteger& v_num, std::vector<int>& q_ans);
    void denormalization_remainder(BigInteger& u_num, std::vector<int>& v_ans, size_t n, unsigned long long d);
public:
    BigInteger();
    BigInteger(int num);
    BigInteger(long long num);
    BigInteger(const std::string& str);
    
    friend bool operator<(const BigInteger& first, const BigInteger& second);
    friend bool operator==(const BigInteger& first, const BigInteger& second);
    explicit operator bool() const;
    std::string toString() const;
    int signum() const;
    void changeSignum();
    BigInteger operator-() const;
    BigInteger& operator++();
    BigInteger operator++(int);
    BigInteger& operator--();
    BigInteger operator--(int);
    BigInteger& operator+=(const BigInteger& num);
    BigInteger& operator-=(const BigInteger& num);
    BigInteger& operator*=(const BigInteger& num);
    BigInteger& operator/=(const BigInteger& num);
    BigInteger& operator%=(const BigInteger& num);

    ~BigInteger();
};

bool operator<(const BigInteger& first, const BigInteger& second);
bool operator>(const BigInteger& first, const BigInteger& second);
bool operator<=(const BigInteger& first, const BigInteger& second);
bool operator>=(const BigInteger& first, const BigInteger& second);
bool operator==(const BigInteger& first, const BigInteger& second);
bool operator!=(const BigInteger& first, const BigInteger& second);

BigInteger operator+(const BigInteger& first, const BigInteger& second);
BigInteger operator-(const BigInteger& first, const BigInteger& second);
BigInteger operator*(const BigInteger& first, const BigInteger& second);
BigInteger operator/(const BigInteger& first, const BigInteger& second);
BigInteger operator%(const BigInteger& first, const BigInteger& second);

std::ostream& operator<<(std::ostream& out, const BigInteger& num);
std::istream& operator>>(std::istream& in, BigInteger& num);

#endif 
