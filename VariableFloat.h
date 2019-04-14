#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

template<int fraction, int exponent>
/// Variable precision floating point number library.
/// \tparam fraction - fraction bit count.
/// \tparam exponent - exponent bit count.
class VariableFloat
{
private:
    //Float and double constants.
    const u_int DOUBLE_EXPONENT = 11;
    const u_int DOUBLE_FRACTION = 52;
    const u_int FLOAT_EXPONENT = 8;
    const u_int FLOAT_FRACTION = 23;

    /// Bias vector.
    std::vector<u_char> biasContainer;

    /// Exponent byte container.
    std::vector<u_char> exponentContainer;

    /// Fraction byte container.
    std::vector<u_char> fractionContainer;

    /// Exponent size in bytes.
    u_int exponentSize{};

    /// Fraction size in bytes.
    u_int fractionSize{};

    /// Sign bit of a number.
    bool sign;

    /// Private constructor for initializing containers.
    VariableFloat();

    /// Copies bytes to a container.
    /// \param source - source byte array.
    /// \param size - array element count.
    /// \param destination - destination vector.
    void putBytes(const u_char * source, u_int size, std::vector<u_char> &destination);

    /// Shifts a vector of bytes 'shift' times right.
    /// \param vector - vector which contents are going to be shifted.
    /// \param size - vector byte count.
    /// \param shift - bit shift count.
    void shiftVectorRight(std::vector<u_char> & vector, int size, int shift);

    /// Creates a bias vector for specified bit exponent bit count.
    /// \param customExponent - exponent bit count.
    /// \return Bias vector for specified bit count.
    std::vector<u_char> createBiasContainerForExponent(int customExponent);

    /// Adds bytes from two containers together (result stored in first).
    /// \param first - first addition operand (vector).
    /// \param second - second addition operand (vector).
    /// \return 0 - if there is no carry, 1 - otherwise.
    bool addBytes(std::vector<u_char> &first, std::vector<u_char> &second);

    /// Subtracts bytes from two containers (result stored in first).
    /// \param first - first subtraction operand (vector).
    /// \param second - second subtraction operand (vector).
    /// \return 0 - if there is no carry, 1 - otherwise.
    bool subtractBytes(std::vector<u_char> &first, std::vector<u_char> &second);

public:
    /// VariableFloat single precision constructor.
    /// \param number - constructor float argument.
    explicit VariableFloat(float number);

    /// VariableFloat double precision constructor.
    /// \param number - constructor double argument.
    explicit VariableFloat(double number);

    ~VariableFloat() = default;

    /// VariableFloat copy constructor.
    VariableFloat(const VariableFloat<fraction, exponent> &number);

    const VariableFloat<fraction, exponent>& operator=(const VariableFloat<fraction, exponent> &number);

    void operator+=(const VariableFloat<fraction, exponent> &operand);

    void operator-=(const VariableFloat<fraction, exponent> &operand);

    void operator*=(const VariableFloat<fraction, exponent> &operand);

    void operator/=(const VariableFloat<fraction, exponent> &operand);

    static VariableFloat<fraction, exponent> sqrt(VariableFloat number);

    /// Prints contents of containers in hex format.
    /// \param str - output stream.
    void printContainers(std::ostream &str) const;
};

template<int fraction, int exponent>
std::ostream& operator<<(std::ostream &str, const VariableFloat<fraction, exponent> &obj)
{
    obj.printContainers(str);
    return str;
}

template<int fraction, int exponent>
std::istream& operator>>(std::istream &str, VariableFloat<fraction, exponent> &obj)
{
    return str;
}

template<int fraction, int exponent>
VariableFloat<fraction,exponent>::VariableFloat()
{
    sign = 0;
    exponentSize = (exponent / 8) + 1;
    fractionSize = (fraction / 8) + 1;

    for (int i = 0; i < exponentSize; ++i) biasContainer.push_back(255);
    int shiftCount = exponentSize * 8 - (exponent - 1);
    shiftVectorRight(biasContainer, exponentSize, shiftCount);
}

template<int fraction, int exponent>
VariableFloat<fraction, exponent>::VariableFloat(const VariableFloat<fraction, exponent> &number) : VariableFloat()
{
    sign = number.sign;
    for (auto byte : number.exponentContainer) exponentContainer.insert(exponentContainer.begin(), byte);
    for (auto byte : number.fractionContainer) fractionContainer.insert(fractionContainer.begin(), byte);
}

template<int fraction, int exponent>
VariableFloat<fraction, exponent>::VariableFloat(float number) : VariableFloat()
{
    u_int floatBytes = *((u_int *) &number);

    //To get the exponent, left shift bits by one to get rid of the sign bit
    //and then right shift by float mantissa bit size.
    u_int floatExponent = floatBytes << 1;
    floatExponent >>= 1;
    sign = ((u_int) floatExponent ^ floatBytes) > 0;
    floatExponent >>= FLOAT_FRACTION;

    //We need to convert our extracted exponent to template implementation.
    putBytes(((u_char *)&floatExponent), exponentSize, exponentContainer);
    std::vector<u_char> floatBias = createBiasContainerForExponent(FLOAT_EXPONENT);
    subtractBytes(exponentContainer, floatBias);
    addBytes(exponentContainer, biasContainer);

    u_int floatFraction = floatBytes << (FLOAT_EXPONENT + 1);
    floatFraction >>= (FLOAT_EXPONENT + 1);
    putBytes(((u_char *)&floatFraction), fractionSize, fractionContainer);

    printf("Float bytes: 0x%X\n", floatBytes);
    printf("Float sign: %d\n", sign);
    printf("Float exponent: 0x%X\n", floatExponent);
    printf("Float fraction: 0x%X\n", floatFraction);
}

template<int fraction, int exponent>
VariableFloat<fraction, exponent>::VariableFloat(double number) : VariableFloat()
{
    u_int64_t doubleBytes = *((uint64_t *) &number);

    //To get the exponent, left shift bits by one to get rid of the sign bit
    //and then right shift by double mantissa bit size.
    u_int64_t doubleExponent = doubleBytes << 1;
    doubleExponent >>= 1;
    sign = ((u_int64_t) doubleExponent ^ doubleBytes) > 0;
    doubleExponent >>= DOUBLE_FRACTION;

    //We need to convert our extracted exponent to template implementation.
    putBytes(((u_char *)&doubleExponent), exponentSize, exponentContainer);
    std::vector<u_char> doubleBias = createBiasContainerForExponent(DOUBLE_EXPONENT);
    subtractBytes(exponentContainer, doubleBias);
    addBytes(exponentContainer, biasContainer);

    u_int64_t doubleFraction = doubleBytes << (DOUBLE_EXPONENT + 1);
    doubleFraction >>= (DOUBLE_EXPONENT + 1);
    putBytes(((u_char *)&doubleFraction), fractionSize, fractionContainer);

    printf("Double bytes: 0x%lX\n", doubleBytes);
    printf("Double sign: %d\n", sign);
    printf("Double exponent: 0x%lX\n", doubleExponent);
    printf("Double fraction: 0x%lX\n", doubleFraction);
}

template<int fraction, int exponent>
void VariableFloat<fraction,exponent>::printContainers(std::ostream &str) const
{
    if (sign) str << "- ";
    else str << "+ ";

    str << "0x";
    for (int i = 0; i < exponentSize; ++i)
    {
        str << std::hex << (unsigned) exponentContainer[i];
    }
    str << " ";

    str << "0x";
    for(int i = 0; i < fractionSize; ++i)
    {
        str << std::hex << (unsigned) fractionContainer[i];
    }
    str << std::endl;
}

template<int fraction, int exponent>
void VariableFloat<fraction,exponent>::putBytes(const u_char * source, u_int size, std::vector<u_char> &destination)
{
    for (int i = 0; i < size; ++i)
    {
        destination.insert(destination.begin(), source[i]);
    }
}

template<int fraction, int exponent>
void VariableFloat<fraction, exponent>::shiftVectorRight(std::vector<u_char> &vector, int size, int shift)
{
    u_char start = shift / 8;
    u_char rest = shift % 8;
    u_char previous = 0;
    for (int i = 0; i < size; ++i)
    {
        if (start <= i) previous = vector[i - start];
        u_char value = (previous << (8 - rest)) | vector[i + start] >> rest;
        vector[i + start] = value;
    }
}

template<int fraction, int exponent>
std::vector<u_char> VariableFloat<fraction, exponent>::createBiasContainerForExponent(int customExponent)
{
    std::vector<u_char> customBias;
    int customExponentSize = (customExponent / 8) + 1;
    customBias.reserve(customExponentSize);
    for (int i = 0; i < customExponentSize; ++i) customBias.push_back(255);

    int shiftCount = customExponentSize * 8 - (customExponent - 1);
    shiftVectorRight(customBias, customExponentSize, shiftCount);
    return customBias;
}

template<int fraction, int exponent>
bool VariableFloat<fraction, exponent>::addBytes(std::vector<u_char> &first, std::vector<u_char> &second)
{
    u_char partialProduct = 0;
    int firstSize = first.size() - 1;
    int secondSize = second.size() - 1;
    bool carry = false;
    for (int i = 0; i == secondSize; ++i)
    {
        partialProduct = first[firstSize - i] + second[secondSize - i];
        carry = partialProduct < first[firstSize - i];
        if (carry) partialProduct++;
        first[firstSize - i] = partialProduct;
    }
    return carry;
}

template<int fraction, int exponent>
bool VariableFloat<fraction, exponent>::subtractBytes(std::vector<u_char> &first, std::vector<u_char> &second)
{
    u_char partialProduct = 0;
    int firstSize = first.size() - 1;
    int secondSize = second.size() - 1;
    bool carry = false;
    for (int i = 0; i == secondSize; ++i)
    {
        partialProduct = first[firstSize - i] - second[secondSize - i];
        carry = partialProduct < first[firstSize - i];
        if (carry) partialProduct++;
        first[firstSize - i] = partialProduct;
    }
    return carry;
}
