#include <iostream>
#include <limits>

#include "big_integer.hpp"
#include "rational.hpp"

void big_integer_dump(const BigInteger& integer);

void rational_dump(const Rational& rational);

int main() {
    
    /*
    BigInteger int1;
    dump(int1);

    int sz2 = 1'178'234'123;
    BigInteger int2(sz2);
    dump(int2);

    long long sz3 = 178;
    BigInteger int3 = sz3;
    dump(int3);

    BigInteger int4("-12345678901234567890");
    dump(int4);

    BigInteger int5("-000");
    dump(int5);


    BigInteger int6("0000000000000000001000000000");
    dump(int6);

    long long num = std::numeric_limits<long long>::min();
    BigInteger int7(num);
    dump(int7);

    std::string str = int7.toString();
    std::cout << "Convert to string: " << str << "\n\n";

    std::cout << "int2 > int3 ? " << (int2 > int3) << '\n';
    std::cout << "int2 < int5 ? " << (int2 < int5) << '\n';
    std::cout << "int7 < int6 ? " << (int7 < int6) << '\n';

    ++int7;
    dump(int7);

    BigInteger int8(1000000000);
    --int8;
    dump(int8);

    int8 = int7++;

    dump(int7);
    dump(int8);

    BigInteger int9("-1999999998");
    BigInteger int10("-999999999");
    int9 -= int10;
    dump(int9);

    BigInteger int11("-25");
    BigInteger int12("-25");
    int11 *= int12;
    dump(int11);

    BigInteger int13("67");
    dump(int13);

    BigInteger int_copy;
    BigInteger int14("-4");
    int_copy = int13 + int14;
    dump(int_copy);
    int_copy = int13 - int14;
    dump(int_copy);
    int_copy = int13 * int14;
    dump(int_copy);
    int_copy = int13 / int14;
    dump(int_copy);
    int_copy = int13 % int14;
    dump(int_copy);
    
    BigInteger int_from_key;
    std::cin >> int_from_key;
    int_from_key += int_from_key;
    dump(int_from_key);

    BigInteger int15("999999999");
    ++int15;
    dump(int15);

    */

    /*Rational r1;
    rational_dump(r1);

    BigInteger num("12345");
    Rational r2(num);
    rational_dump(r2);

    Rational r3(-37);
    rational_dump(r3);
    */

    /*
    BigInteger num1("2000000000");
    BigInteger num2("999999999");
    Rational r4(num1, num2);
    rational_dump(r4);

    //std::string str = r4.toString();
    //std::cout << str << '\n';

    std::cout << "asDecimal = " << r4.asDecimal(10) << '\n';
    std::cout << "double " << (double)r4 << '\n';
    */

    /*
    BigInteger num3("-499999999"), num4("1000000000");
    BigInteger num5("-511111111"), num6("1000000000");
    Rational r5(num3, num4);
    Rational r6(num5, num6);
    
    //r5 /= r6;
    //rational_dump(r6);
    //rational_dump(r5);

    std::cout << "compare result = " << (r5 > r6) << '\n';
    */

    Rational from_keyboard;
    std::cin >> from_keyboard;
    rational_dump(from_keyboard);
    std::cout << from_keyboard << '\n';
}

void big_integer_dump(const BigInteger& integer) {
   
    std::cout << "is positive = " << integer.signum() << '\n'; 
    std::cout << integer << '\n';
}

void rational_dump(const Rational& rational) {
   std::cout << "numerator:\n";
   big_integer_dump(rational.get_numerator());
   std::cout << "denominator:\n";
   big_integer_dump(rational.get_denominator());
   std::cout << "conical form " << rational.toString();
   std::cout << "\n\n";
}
