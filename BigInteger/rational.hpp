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
    
    const BigInteger& get_numerator() const;
    const BigInteger& get_denominator() const;

    std::string toString() const;
    std::string asDecimal(size_t precision) const;
    explicit operator double() const;
};

void reduce_fractions(BigInteger& numerator, BigInteger& denominator);
void find_maximum(BigInteger& bigger, BigInteger& smaller);


#endif
