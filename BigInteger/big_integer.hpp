#ifndef BIG_INTEGER_HPP
#define BIG_INTEGER_HPP

#include <vector>
#include <string>

class BigInteger {
private:
    std::vector<int> digits;
    static const int base = 1e9;
    bool is_positive = true;
    void convert_system(unsigned long long num);
    static int max_digits_len();
    static int get_base();
public:
    BigInteger();
    BigInteger(int num);
    BigInteger(long long num);
    BigInteger(const std::string& str);
    
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




#endif 
