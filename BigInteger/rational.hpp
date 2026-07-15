#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include "big_integer.hpp"

class Rational {
private:
    BigInteger numerator;                                                    // числитель
    BigInteger denominator;                                                  // знаменатель
    void get_conical_form();
public:
    Rational();
    Rational(const BigInteger& num);
    Rational(int num);
    Rational(const BigInteger& numerator, const BigInteger& denominator);
    Rational(const Rational& fraction);                                      // copy constructor
    Rational& operator=(const Rational& fraction) &;                         // only lvalue
    
    const BigInteger& get_numerator() const;
    const BigInteger& get_denominator() const;

    std::string toString() const;
    std::string asDecimal(size_t precision) const;
    explicit operator double() const;
 
    Rational& operator+=(const Rational& fraction);
    Rational& operator-=(const Rational& fraction);
    Rational& operator*=(const Rational& fraction);
    Rational& operator/=(const Rational& fraction);
    Rational operator-() const;
    friend bool operator<(const Rational& first, const Rational& second);
    friend bool operator==(const Rational& first, const Rational& second);
    friend std::istream& operator>>(std::istream& in, Rational& fraction);

    ~Rational();
};

void reduce_fractions(BigInteger& numerator, BigInteger& denominator);
void find_maximum(BigInteger& bigger, BigInteger& smaller);

Rational operator+(const Rational& first, const Rational& second);
Rational operator-(const Rational& first, const Rational& second);
Rational operator*(const Rational& first, const Rational& second);
Rational operator/(const Rational& first, const Rational& second);

bool operator>(const Rational& first, const Rational& second);
bool operator<=(const Rational& first, const Rational& second);
bool operator>=(const Rational& first, const Rational& second);
bool operator!=(const Rational& first, const Rational& second);

std::ostream& operator<<(std::ostream& out, const Rational& fraction);

#endif
