#include <iostream>
#include <algorithm>
#include <memory_resource>

#include "rational.hpp"

// Constructors
Rational::Rational(): numerator(0), denominator(1) {}

Rational::Rational(const BigInteger& num): numerator(num), denominator(1) {}

Rational::Rational(int num): Rational(BigInteger(num)) {}

Rational::Rational(const BigInteger& numerator, const BigInteger& denominator): numerator(numerator), denominator(denominator) {
    reduce_fractions(this->numerator, this->denominator);
    this->get_conical_form();
}

Rational::Rational(const Rational& fraction): Rational(fraction.numerator, fraction.denominator) {}

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

// Methods
std::string Rational::toString() const {
    std::string fraction;
    if (numerator == 0) {
        fraction.push_back('0');
        return fraction;
    }

    if (denominator == 1) {
        return numerator.toString();
    }
 
    int numerator_sign = numerator.signum(), denominator_sign = denominator.signum();
    int signum = numerator_sign * denominator_sign;
    std::string numerator_str = numerator.toString(), denominator_str = denominator.toString();
    size_t fraction_start = 0, numerator_start = 0, denominator_start = 0;

    if (numerator_sign == -1) ++numerator_start;
    if (denominator_sign == -1) ++denominator_start;
    if (signum == -1) {
        ++fraction_start;
        fraction.push_back('-');
    }

    fraction.insert(fraction.begin() + fraction_start, numerator_str.begin() + numerator_start, numerator_str.end());
    fraction.push_back('/');
    fraction.insert(fraction.end(), denominator_str.begin() + denominator_start, denominator_str.end());

    return fraction;
}

std::string Rational::asDecimal(size_t precision) const {
    std::string fractional;
    if (numerator == 0) {
        fractional.push_back('0');
        if (precision == 0) return fractional;
        fractional.push_back('.');
        fractional.insert(fractional.end(), precision, '0');
        return fractional;
    }
    
    std::string numerator_str = numerator.toString();
    if (denominator == 1) {
        fractional.insert(fractional.begin(), numerator_str.begin(), numerator_str.end());
        if (precision == 0) return fractional;
        fractional.push_back('.');
        fractional.insert(fractional.end(), precision, '0');
        return fractional;
    }

    BigInteger integer_part = numerator / denominator;
    BigInteger fractional_part = numerator % denominator;

    std::string int_part_str = integer_part.toString(), fract_part_str = fractional_part.toString();
    int int_sign = integer_part.signum(), fract_sign = fractional_part.signum(), denom_sign = denominator.signum();
    int signum = numerator.signum() * denominator.signum();
    size_t fractional_start = 0, int_part_start = 0, fract_part_start = 0;
    if (signum == -1){
        ++fractional_start;
        fractional.push_back('-');
    }
    if (int_sign == -1) ++int_part_start;
    if (fract_sign == -1) ++fract_part_start;
    fractional.insert(fractional.begin() + fractional_start, int_part_str.begin() + int_part_start, int_part_str.end());
    if (precision == 0) return fractional;

    fractional.push_back('.');

    size_t counter = 0;
    BigInteger copy_denom = denominator, new_int_part;
    if (denom_sign == -1) copy_denom.changeSignum();
    if (fract_sign == -1) fractional_part.changeSignum();
    while (counter < precision && fractional_part != 0) {
        fractional_part *= 10;
        new_int_part = fractional_part / copy_denom;
        fractional_part = fractional_part % copy_denom;
        fractional += (new_int_part.toString());
        ++counter;
    }
    
    if (counter < precision) fractional.insert(fractional.end(), precision - counter, '0');
    return fractional;
}

Rational::operator double() const {
    const size_t max_digits = 18;                             // максимальное количество цифр после запятой у double + 1
    return std::stod(this->asDecimal(max_digits));
}

Rational& Rational::operator=(const Rational& fraction) & {
    numerator = fraction.numerator;
    denominator = fraction.denominator;

    return *this;
}

Rational& Rational::operator+=(const Rational& fraction) {
    numerator = numerator * fraction.denominator + denominator * fraction.numerator;
    denominator *= fraction.denominator;
    reduce_fractions(numerator, denominator);
    this->get_conical_form();
    return *this;
}

Rational& Rational::operator-=(const Rational& fraction) {
    numerator = numerator * fraction.denominator - denominator * fraction.numerator;
    denominator *= fraction.denominator;
    reduce_fractions(numerator, denominator);
    this->get_conical_form();
    return *this;
}

Rational& Rational::operator*=(const Rational& fraction) {
    numerator *= fraction.numerator;
    denominator *= fraction.denominator;
    reduce_fractions(numerator, denominator);
    this->get_conical_form();
    return *this;
}

Rational& Rational::operator/=(const Rational& fraction) {
    Rational copy = fraction;
    copy.numerator.swap(copy.denominator);
    copy.get_conical_form();
    *this *= copy;
    return *this;
}

Rational Rational::operator-() const {
    Rational copy = *this;
    copy.numerator.changeSignum();
    return copy;
}

// Functions
Rational operator+(const Rational& first, const Rational& second) {
    Rational copy = first;
    copy += second;
    return copy;
}

Rational operator-(const Rational& first, const Rational& second) {
    Rational copy = first;
    copy -= second;
    return copy;
}

Rational operator*(const Rational& first, const Rational& second) {
    Rational copy = first;
    copy *= second;
    return copy;
}

Rational operator/(const Rational& first, const Rational& second) {
    Rational copy = first;
    copy /= second;
    return copy;
}

bool operator<(const Rational& first, const Rational& second) {
    return first.numerator * second.denominator < second.numerator * first.denominator;
}

bool operator==(const Rational& first, const Rational& second) {
    if (first.numerator   != second.numerator)   return false;
    if (first.denominator != second.denominator) return false;
    
    return true;
}

bool operator>(const Rational& first, const Rational& second) {
    return second < first;
}

bool operator<=(const Rational& first, const Rational& second) {
    return !(first > second);
}

bool operator>=(const Rational& first, const Rational& second) {
    return !(first < second);
}

bool operator!=(const Rational& first, const Rational& second) {
    return !(first == second);
}

// Getters
const BigInteger& Rational::get_numerator() const {
    return this->numerator;
}

const BigInteger& Rational::get_denominator() const {
    return this->denominator;
}

std::ostream& operator<<(std::ostream& out, const Rational& fraction) {
    std::string fract_str = fraction.toString();
    out << fract_str;
    return out;
}

std::istream& operator>>(std::istream& in, Rational& second) {
    std::string fraction;
    in >> fraction;

    size_t offset = fraction.find('/');
    if (offset == std::string::npos) {
        second.numerator = BigInteger(fraction);
        second.denominator = BigInteger(1);
        return in;
    }
    
    std::string int_str = fraction.substr(0, offset);
    std::string fract_str = fraction.substr(offset + 1, fraction.size());

    second.numerator = BigInteger(int_str);
    second.denominator = BigInteger(fract_str);
    reduce_fractions(second.numerator, second.denominator);
    second.get_conical_form();
    return in;
}

// Destructor
Rational::~Rational() = default;
