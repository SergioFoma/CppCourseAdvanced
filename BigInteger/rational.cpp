#include <iostream>

#include "rational.hpp"

// Constructors
Rational::Rational(): numerator(0), denominator(1) {}

Rational::Rational(const BigInteger& num): numerator(num), denominator(1) {}

Rational::Rational(int num): Rational(BigInteger(num)) {}

Rational::Rational(const BigInteger& numerator, const BigInteger& denominator): numerator(numerator), denominator(denominator) {
    reduce_fractions(this->numerator, this->denominator);
    this->get_conical_form();
}

// Local functions
void Rational::get_conical_form() {
    if (denominator.signum() == -1) {
        numerator.changeSignum();
        denominator.changeSignum();
    }
}

void find_maximum(BigInteger& bigger, BigInteger& smaller) {
   if (bigger < smaller) smaller.swap(bigger); 
}

void reduce_fractions(BigInteger& numerator, BigInteger& denominator) {
    if (numerator == 0) {
        denominator = 1;
        return ;
    }

    BigInteger bigger = numerator, smaller = denominator, remains;
    if (bigger < 0) bigger.changeSignum();
    if (smaller < 0) smaller.changeSignum();
    do {
        find_maximum(bigger, smaller);
        remains = bigger % smaller;
        bigger = remains;
    } while (remains != 0);

    numerator /= smaller;
    denominator /= smaller;
}

// Getters
const BigInteger& Rational::get_numerator() const {
    return this->numerator;
}

const BigInteger& Rational::get_denominator() const {
    return this->denominator;
}
