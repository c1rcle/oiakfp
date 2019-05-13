#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

#include "ByteArray.h"

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
    /// Maximum exponent value for current representation (standard hex).
    std::vector<u_char> maxExponent;
    /// Minimum exponent value for current representation (standard hex).
    std::vector<u_char> minExponent;
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
    /// Converts a hexadecimal string into a byte array.
    /// \param input - input string.
    /// \return Vector of bytes corresponding to string's value.
    std::vector<u_char> hexStringToBytes(const std::string &input);
public:
    /// Creates a bias vector for specified bit exponent bit count.
    /// \param customExponent - exponent bit count.
    /// \return Bias vector for specified bit count.
    std::vector<u_char> createBiasContainerForExponent(int customExponent);
    /// VariableFloat single precision constructor.
    /// \param number - constructor float argument.
    explicit VariableFloat(float number);
    /// VariableFloat double precision constructor.
    /// \param number - constructor double argument.
    explicit VariableFloat(double number);
    /// VariableFloat hex constructor.
    /// \param exponentRep - exponent representation given in hex string.
    /// \param fractionRep - fraction representation given in hex string.
    VariableFloat(bool sign, std::string exponentRep, std::string fractionRep);
    /// VariableFloat destructor.
    ~VariableFloat() = default;
    /// VariableFloat copy constructor.
    VariableFloat(const VariableFloat<fraction, exponent> &number);
    /// Assignment operator declaration.
    /// \param number - number that should be assigned to 'this'.
    /// \return Class object reference.
    const VariableFloat<fraction, exponent>& operator=(const VariableFloat<fraction, exponent> &number);
    /// Adds 'operand' to current object.
    /// \param operand - reference to VariableFloat object with same template parameters.
    void operator+=(const VariableFloat<fraction, exponent> &operand);
    /// Subtracts 'operand' from current object.
    /// \param operand - reference to VariableFloat object with same template parameters.
    void operator-=(const VariableFloat<fraction, exponent> &operand);
    /// Multiplies current object by 'operand'.
    /// \param operand - reference to VariableFloat object with same template parameters.
    void operator*=(const VariableFloat<fraction, exponent> &operand);
    /// Divides current object by 'operand'.
    /// \param operand - reference to VariableFloat object with same template parameters.
    void operator/=(const VariableFloat<fraction, exponent> &operand);

    //static VariableFloat<fraction, exponent> sqrt(VariableFloat number) - TODO (maybe).

    /// Prints contents of containers in hex format.
    /// \param str - output stream.
    void printContainers(std::ostream &str) const;
    /// Checks whether currently stored number is a NaN.
    /// \return true if NaN, otherwise false.
    bool isNan() const;
    /// Checks whether currently stored number is infinity (number is too big).
    /// \return true if Infinity, otherwise false.
    bool isInfinity() const;
    /// Checks whether currently stored number represents negative infinity.
    /// \return true if -Infinity, otherwise false.
    bool isNegativeInfinity() const;
    /// Checks whether currently stored number represents positive infinity.
    /// \return true if +Infinity, otherwise false.
    bool isPositiveInfinity() const;
};

template<int fraction, int exponent>
std::ostream& operator<<(std::ostream &str, const VariableFloat<fraction, exponent> &obj)
{
    //Prints the contents of containers using str.
    obj.printContainers(str);
    return str;
}

template<int fraction, int exponent>
std::istream& operator>>(std::istream &str, VariableFloat<fraction, exponent> &obj)
{
    //TODO
    return str;
}

template<int fraction, int exponent>
VariableFloat<fraction,exponent>::VariableFloat()
{
    sign = 0;
    exponentSize = (exponent / 8) + 1;
    fractionSize = (fraction / 8) + 1;

    for (unsigned int i = 0; i < exponentSize; ++i)
    {
        biasContainer.push_back(255);
        maxExponent.push_back(255);
        minExponent.push_back(0);
    }

    int shiftCount = exponentSize * 8 - (exponent - 1);
    ByteArray::shiftVectorRight(biasContainer, shiftCount);

    shiftCount++;
    ByteArray::shiftVectorRight(maxExponent, shiftCount);
    ByteArray::subtractBytes(maxExponent, biasContainer);
    ByteArray::subtractBytes(minExponent, biasContainer);
}

template<int fraction, int exponent>
VariableFloat<fraction, exponent>::VariableFloat(const VariableFloat<fraction, exponent> &number) : VariableFloat()
{
    sign = number.sign;
    for (auto byte : number.exponentContainer) exponentContainer.push_back(byte);
    for (auto byte : number.fractionContainer) fractionContainer.push_back(byte);
    for (auto byte : number.biasContainer) biasContainer.push_back(byte);
    for (auto byte : number.maxExponent) maxExponent.push_back(byte);
    for (auto byte : number.minExponent) minExponent.push_back(byte);
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
    int byteCount = exponent >= FLOAT_EXPONENT ? (FLOAT_EXPONENT / 8) + 1 : exponentSize;
    ByteArray::putBytes(((u_char *)&floatExponent), byteCount, exponentContainer);
    for (unsigned int i = 0; i < (exponentSize - byteCount); i++) exponentContainer.push_back(0);
    std::vector<u_char> floatBias = createBiasContainerForExponent(FLOAT_EXPONENT);
    ByteArray::subtractBytes(exponentContainer, floatBias);
    //TODO compare exponents to determine if they can be fit in this representation.
    ByteArray::addBytes(exponentContainer, biasContainer);

    u_int floatFraction = floatBytes << (FLOAT_EXPONENT + 1);
    floatFraction >>= (FLOAT_EXPONENT + 1);
    byteCount = fraction >= FLOAT_FRACTION ? (FLOAT_FRACTION / 8) + 1: fractionSize;
    ByteArray::putBytes(((u_char *)&floatFraction), byteCount, fractionContainer);
    for (unsigned int i = 0; i < (fractionSize - byteCount); i++) fractionContainer.push_back(0);
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
    int byteCount = exponent >= DOUBLE_EXPONENT ? (DOUBLE_EXPONENT / 8) + 1 : exponentSize;
    ByteArray::putBytes(((u_char *)&doubleExponent), byteCount, exponentContainer);
    for (unsigned int i = 0; i < (exponentSize - byteCount); i++) exponentContainer.push_back(0);
    std::vector<u_char> doubleBias = createBiasContainerForExponent(DOUBLE_EXPONENT);
    ByteArray::subtractBytes(exponentContainer, doubleBias);
    //TODO compare exponents to determine if they can be fit in this representation.
    ByteArray::addBytes(exponentContainer, biasContainer);

    u_int64_t doubleFraction = doubleBytes << (DOUBLE_EXPONENT + 1);
    doubleFraction >>= (DOUBLE_EXPONENT + 1);
    byteCount = fraction >= DOUBLE_FRACTION ? (DOUBLE_FRACTION / 8) + 1: fractionSize;
    ByteArray::putBytes(((u_char *)&doubleFraction), byteCount, fractionContainer);
    for (unsigned int i = 0; i < (fractionSize - byteCount); i++) fractionContainer.push_back(0);
}

template<int fraction, int exponent>
VariableFloat<fraction, exponent>::VariableFloat(bool sign, std::string exponentRep, std::string fractionRep) : VariableFloat()
{
    this->sign = sign;
    exponentContainer = hexStringToBytes(exponentRep);
    int byteCount = exponentContainer.size();
    for (unsigned int i = 0; i < (exponentSize - byteCount); i++) exponentContainer.insert(exponentContainer.begin(), 0);
    ByteArray::addBytes(exponentContainer, biasContainer);
    fractionContainer = hexStringToBytes(fractionRep);
}

template<int fraction, int exponent>
void VariableFloat<fraction,exponent>::printContainers(std::ostream &str) const
{
    //Write sign to output stream.
    if (sign) str << "- ";
    else str << "+ ";

    if (isInfinity())
    {
        str << "inf";
        return;
    }
    else if (isNan())
    {
        str << "NaN";
    }
    else
    {
        std::vector<u_char> copy(exponentContainer);

        //if(!ByteArray::checkIfZero(exponentContainer))
        //    ByteArray::subtractBytes(copy, biasContainer);

        str << "0x";

        for (unsigned int i = 0; i < copy.size(); ++i)
        {
            str << std::hex << std::setfill('0') << std::setw(2) << (unsigned) exponentContainer[i];
        }
        str << " ";

        str << "0x";
        for(unsigned int i = 0; i < fractionSize; ++i)
        {
            str << std::hex << std::setfill('0') << std::setw(2) << (unsigned) fractionContainer[i];
        }
        str << std::endl;
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
    ByteArray::shiftVectorRight(customBias, shiftCount);
    return customBias;
}

template<int fraction, int exponent>
std::vector<u_char> VariableFloat<fraction, exponent>::hexStringToBytes(const std::string &input)
{
    std::vector<u_char> bytes;
    for (unsigned int i = 0; i < input.size(); i+=2)
    {
        std::string stringByte = input.substr(i, 2);
        auto byte = (u_char) strtol(stringByte.c_str(), NULL, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

template<int fraction, int exponent>
bool VariableFloat<fraction, exponent>::isNan() const
{
    for (unsigned int i = 0; i < exponentContainer.size(); ++i)
    {
        if (exponentContainer[i] != 255)
            return false;
    }

    bool fractionSet = false;
    for (unsigned int i = 0; i < exponentContainer.size(); ++i)
    {
        if (exponentContainer[i] != 0)
        {
            fractionSet = true;
            break;
        }
    }
    return fractionSet;
}

template<int fraction, int exponent>
bool VariableFloat<fraction, exponent>::isInfinity() const
{
    for (unsigned int i = 0; i < exponentContainer.size(); ++i)
    {
        if (exponentContainer[i] != 255)
            return false;
    }

    for (unsigned int i = 0; i < exponentContainer.size(); ++i)
    {
        if (exponentContainer[i] != 0)
            return false;
    }
    return true;
}

template<int fraction, int exponent>
bool VariableFloat<fraction, exponent>::isNegativeInfinity() const
{
    return !sign && isInfinity();
}

template<int fraction, int exponent>
bool VariableFloat<fraction, exponent>::isPositiveInfinity() const
{
    return sign && isInfinity();
}