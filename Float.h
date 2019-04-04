#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

void addBytes(u_char * firstContainer, u_char * secondContainer, int size);

//Fraction and exponent are bit counts.
template<int fraction, int exponent>
class Float
{
private:

    //Float and double constants.
    const u_int DOUBLE_EXPONENT = 11;
    const u_int DOUBLE_FRACTION = 52;
    const u_int FLOAT_EXPONENT = 8;
    const u_int FLOAT_FRACTION = 23;

    //Byte containers for exponent and fraction.
    u_char * exponentContainer;
    u_char * fractionContainer;

    //Size of exponent and fraction in bytes.
    u_int exponentSize;
    u_int fractionSize;

    //Sign bit of a number.
    bool sign;

    //Private constructor for initializing containers.
    Float();

    //Used to copy bytes to a container.
    void putBytes(const u_char * source, u_int size, u_char * destination);

public:

    explicit Float(float number);
    explicit Float(double number);
    ~Float();

    Float(const Float<fraction, exponent>& number);

    //Operators declaration.
    const Float<fraction, exponent>& operator=(const Float<fraction, exponent>& number);

    void operator+=(const Float<fraction, exponent>& operand);

    void operator-=(const Float<fraction, exponent>& operand);

    void operator*=(const Float<fraction, exponent>& operand);

    void operator/=(const Float<fraction, exponent>& operand);

    static Float<fraction, exponent> sqrt(Float number);

    void printContainers(std::ostream& str);
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
    sign = 0;

    exponentSize = (exponent / 8) + 1;
    fractionSize = (fraction / 8) + 1;

    exponentContainer = new u_char[exponentSize];
    fractionContainer = new u_char[fractionSize];

}

template<int fraction, int exponent>
Float<fraction, exponent>::Float(float number) : Float()
{
    u_int floatBytes = *((u_int *) &number);

    //To get the exponent, left shift bits by one to get rid of the sign bit
    //and then right shift by float mantissa bit size.
    u_int floatExponent = floatBytes << 1;
    floatExponent >>= 1;
    sign = ((u_int) floatExponent ^ floatBytes) > 0;
    floatExponent >>= FLOAT_FRACTION;

    u_int floatFraction = floatBytes << (FLOAT_EXPONENT + 1);
    floatFraction >>= (FLOAT_EXPONENT + 1);

    putBytes(((u_char *)&floatFraction), sizeof(floatFraction), fractionContainer);
    putBytes(((u_char *)&floatExponent), sizeof(floatExponent), exponentContainer);
    printf("Float bytes: 0x%X\n", floatBytes);
    printf("Float sign: %d\n", sign);
    printf("Float exponent: 0x%X\n", floatExponent);
    printf("Float fraction: 0x%X\n", floatFraction);
}

template<int fraction, int exponent>
Float<fraction, exponent>::Float(double number) : Float()
{
    u_int64_t doubleBytes = *((uint64_t *) &number);

    //To get the exponent, left shift bits by one to get rid of the sign bit
    //and then right shift by double mantissa bit size.
    u_int64_t doubleExponent = doubleBytes << 1;
    doubleExponent >>= 1;
    sign = ((u_int64_t) doubleExponent ^ doubleBytes) > 0;
    doubleExponent >>= DOUBLE_FRACTION;

    u_int64_t doubleFraction = doubleBytes << (DOUBLE_EXPONENT + 1);
    doubleFraction >>= (DOUBLE_EXPONENT + 1);

    putBytes(((u_char *)&doubleFraction), sizeof(doubleFraction), fractionContainer);
    putBytes(((u_char *)&doubleExponent), sizeof(doubleExponent), exponentContainer);
    printf("Double bytes: 0x%lX\n", doubleBytes);
    printf("Double sign: %d\n", sign);
    printf("Double exponent: 0x%lX\n", doubleExponent);
    printf("Double fraction: 0x%lX\n", doubleFraction);
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
    if (sign) str << "-";
    else str << "+";

    for (int i = 0; i < exponentSize; ++i)
    {
        str << std::hex << ((*((unsigned int *)&exponentContainer[i])) & 0xFF);
    }
    str << " ";

    for(int i = 0; i < fractionSize; ++i)
    {
        str << std::hex << ((*((unsigned int *)&fractionContainer[i])) & 0xFF);
    }
    str << std::endl;
}

template<int fraction, int exponent>
void Float<fraction,exponent>::putBytes(const u_char * source, u_int size, u_char * destination)
{
    for (int i = 0; i < size; ++i)
    {
        destination[i] = source[i];
    }
}