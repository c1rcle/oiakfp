#include <iostream>

template<int fraction, int exponent>
class Float
{
private:
    char* exponentContainer;

    char* fractionContainer;

public:
    Float();
    ~Float();

    Float(const Float<fraction, exponent>& f);
    const Float<fraction, exponent>& operator=(const Float<fraction, exponent>& f);

    /*static Float<fraction, exponent> operator+(const Float<fraction, exponent>& op1,
                                               const Float<fraction, exponent>& op2);*/

    void operator+=(const Float<fraction, exponent>& operand);

    /*static Float<fraction, exponent> operator-(const Float<fraction, exponent>& op1,
                                               const Float<fraction, exponent>& op2);*/

    void operator-=(const Float<fraction, exponent>& operand);

    /*static Float<fraction, exponent> operator*(const Float<fraction, exponent>& multiplicand,
                                               const Float<fraction, exponent>& multiplier);*/

    void operator*=(const Float<fraction, exponent>& operand);

    /*static Float<fraction, exponent> operator*(const Float<fraction, exponent>& divident,
                                               const Float<fraction, exponent>& devisor);*/

    void operator/=(const Float<fraction, exponent>& operand);

    static Float<fraction, exponent> sqrt();

};

template<int fraction, int exponent>
std::ostream operator<<(std::ostream& str, const Float<fraction, exponent>& obj)
{
    return str;
}

template<int fraction, int exponent>
std::istream operator>>(std::istream& str, Float<fraction, exponent>& obj)
{
    return str;
}