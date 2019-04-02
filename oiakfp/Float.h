#include <iostream>
#include <vector>
#include <iomanip>

#pragma once

typedef unsigned long long uLong;
const int doubleExponent = 11;
const int doubleFraction= 52;
const int floatExponent = 8;
const int floatFraction= 23;


//fraction and exponent are bits count
template<int fraction, int exponent>
class Float
{
private:
    unsigned char* exponentContainer;
    unsigned char* fractionContainer;

    int exponentSize;
    int fractionSize;

    bool sign;

    Float();
public:

    Float(float f);
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

    void printContainers(std::ostream& str);

private:
    void putBytes(unsigned char* bytes, int size, unsigned char* dst);

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

template<int fraction, int exponent>
Float<fraction,exponent>::Float()
{
    sign=0;

    exponentSize = (exponent/8)+1;
    fractionSize = (fraction/8)+1;

    exponentContainer = new unsigned char[exponentSize];
    fractionContainer = new unsigned char[fractionSize];

}

template<int fraction, int exponent>
Float<fraction, exponent>::Float(float f) : Float()
{
    unsigned int bytes = *((unsigned int*)&f);
    printf("bytes: 0x%X\n",bytes);

    unsigned int exp = bytes<<1;
    exp >>= 1;
    sign = exp^bytes;

    exp >>= floatFraction;

    printf("exponent: 0x%X\n",exp);

    unsigned int frac = bytes<< floatExponent + 1;
    frac >>= floatExponent + 1;

    printf("fraction: 0x%X\n",frac);

    putBytes(((unsigned char*)&frac), sizeof(frac), fractionContainer);
    putBytes(((unsigned char*)&exp), sizeof(exp), exponentContainer);
}


template<int fraction, int exponent>
Float<fraction,exponent>::~Float()
{
    delete[] exponentContainer;
    delete[] fractionContainer;
}

template<int fraction, int exponent>
void Float<fraction,exponent>::printContainers(std::ostream &str)
{
    if(sign) str<<"+";
    else str<<"-";

    for(int i=0;i<exponentSize;++i){
        str<<std::hex<<((*((unsigned int*)&exponentContainer[i]))&0xFF);
    }
    str<<" ";

    for(int i=0;i<fractionSize;++i){
        str<<std::hex<<((*((unsigned int*)&fractionContainer[i]))&0xFF);
    }
    str<<std::endl;
}

template<int fraction, int exponent>
void Float<fraction,exponent>::putBytes(unsigned char *bytes, int size, unsigned char *dst)
{
    for(int i=0;i<size;++i){
        dst[i]=bytes[i];
    }
}


