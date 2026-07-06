#ifndef BIG_INTEGER_HPP
#define BIG_INTEGER_HPP

#include <vector>
#include <string>

class BigInteger {
private:
    std::vector<int> digits;
    const int base = 1e9;
    bool is_positive = true;
    void convert_system(unsigned long long num);
    int max_digits_len() const;
public:
    BigInteger();
    BigInteger(int num);
    BigInteger(long long num);
    BigInteger(const std::string& str);

    const std::vector<int>& get_digits() const;             // FOR DEBUG
    int get_base() const;                                   // FOR DEBUG
    bool get_sign() const;                                  // FRO DEBUG

    ~BigInteger();
};






#endif 
