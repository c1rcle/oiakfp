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
    bool sign{};

    /// Converts a hexadecimal string into a byte array.
    /// \param input - input string.
    /// \return Vector of bytes corresponding to string's value.
    std::vector<u_char> hexStringToBytes(const std::string &input);

    /// Rounds the fraction using 'round to nearest' method.
    /// \param currentFraction - current fraction byte container.
    /// \return Reference to a modified byte container.
    std::vector<u_char> &roundFraction(std::vector<u_char> &currentFraction);

    /// Private constructor for initializing containers.
    VariableFloat();
public:

    /// Checks whether current exponent will lead to an overflow or underflow.
    /// \param currentExponent - current exponent byte container.
    /// \return 1 if overflow, -1 if underflow, otherwise 0.
    int checkForOverflow(std::vector<u_char> &currentExponent);

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
    VariableFloat(bool sign, const std::string& exponentRep, const std::string& fractionRep);

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

    /// Checks whether currently stored number is zero.
    /// \return true if zero, otherwise false.
    bool isZero() const;

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

    /// Returns a reference to an object's maxExponent container.
    /// \return reference to an object's maxExponent container.
    const std::vector<u_char> &getMaxExponent() const { return maxExponent; }

    /// Returns a reference to an object's minExponent container.
    /// \return reference to an object's minExponent container.
    const std::vector<u_char> &getMinExponent() const { return minExponent; }

    /// Returns a reference to an object's fraction container.
    /// \return reference to an object's fraction container
    const std::vector<u_char> &getFractionContainer() const { return fractionContainer; }

    /// Returns a reference to an object's exponent container.
    /// \return reference to an object's exponent container
    const std::vector<u_char> &getExponentContainer() const { return exponentContainer; }

    /// Returns sign of a number.
    /// \return true if positive, otherwise false.
    bool getSign() const { return sign; }

    /// Sets fraction container using the argument's vector.
    /// \param f - container to be set.
    void setFractionContainer(std::vector<u_char>& f)
    {
        fractionContainer = roundFraction(f);
        int difference = fractionContainer.size() - fractionSize;
        for (int i = 0; i < difference; i++) fractionContainer.pop_back();
    }

    /// Sets exponent container using the argument's vector.
    /// \param e - container to be set
    void setExponentContainer(std::vector<u_char>& e)
    {
        switch (checkForOverflow(e))
        {
            case 1:
                setInfinity(getSign());
                break;
            case -1:
                setZero(getSign());
                break;
            default:
                exponentContainer = e;
        }
    }

    /// Sets the sign of a number.
    /// \param s - sign to be set.
    void setSign(bool s) { sign = s; }

    /// Sets the object's number representation to zero.
    /// \param setSign - if true then negative, otherwise positive.
    void setZero(bool setSign);

    /// Sets the object's number representation to positive or negative infinity.
    /// \param setSign - if true then negative, otherwise positive.
    void setInfinity(bool setSign);

    /// Sets the object's number representation to NaN.
    void setNan();

    /// Returns a reference to an object's bias container.
    /// \return Reference to a bias container.
    const std::vector<u_char> &getBias() const { return biasContainer; }

    /// Returns object's string representation.
    /// \return Object's string representation.
    std::string toBinary() const;
};

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

    shiftCount--;
    ByteArray::shiftVectorRight(maxExponent, shiftCount);
    ByteArray::setBit(maxExponent, exponent - 1, false);
    ByteArray::setBit(minExponent, exponent - 1, true);
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
const VariableFloat<fraction, exponent> &VariableFloat<fraction, exponent>::operator=(const VariableFloat<fraction, exponent> &number)
{
    sign = number.sign;
    for (auto byte : number.exponentContainer) exponentContainer.push_back(byte);
    for (auto byte : number.fractionContainer) fractionContainer.push_back(byte);
    for (auto byte : number.biasContainer) biasContainer.push_back(byte);
    for (auto byte : number.maxExponent) maxExponent.push_back(byte);
    for (auto byte : number.minExponent) minExponent.push_back(byte);

    return *this;
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
    floatFraction >>= FLOAT_EXPONENT;
    byteCount = fraction >= FLOAT_FRACTION ? (FLOAT_FRACTION / 8) + 1: fractionSize;
    ByteArray::putBytes(((u_char *) &floatFraction), byteCount, fractionContainer);
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
    ByteArray::putBytes(((u_char *) &doubleExponent), byteCount, exponentContainer);
    for (unsigned int i = 0; i < (exponentSize - byteCount); i++) exponentContainer.push_back(0);
    std::vector<u_char> doubleBias = createBiasContainerForExponent(DOUBLE_EXPONENT);
    ByteArray::subtractBytes(exponentContainer, doubleBias);
    //TODO compare exponents to determine if they can be fit in this representation.
    ByteArray::addBytes(exponentContainer, biasContainer);

    u_int64_t doubleFraction = doubleBytes << (DOUBLE_EXPONENT + 1);
    doubleFraction >>= (DOUBLE_EXPONENT + 1);
    byteCount = fraction >= DOUBLE_FRACTION ? (DOUBLE_FRACTION / 8) + 1 : fractionSize;
    ByteArray::putBytes(((u_char *) &doubleFraction), byteCount, fractionContainer);
    for (unsigned int i = 0; i < (fractionSize - byteCount); i++) fractionContainer.push_back(0);
    //Get rid of four zeroes in front (little endian).
    ByteArray::shiftVectorLeft(fractionContainer, 4);
}

template<int fraction, int exponent>
VariableFloat<fraction, exponent>::VariableFloat(bool sign, const std::string &exponentRep,
                                                 const std::string &fractionRep) : VariableFloat()
{
    this->sign = sign;
    exponentContainer = hexStringToBytes(exponentRep);
    int byteCount = exponentContainer.size();
    for (unsigned int i = 0; i < (exponentSize - byteCount); i++) exponentContainer.insert(exponentContainer.begin(), 0);
    ByteArray::addBytes(exponentContainer, biasContainer);
    fractionContainer = hexStringToBytes(fractionRep);
    byteCount = fractionContainer.size();
    for (unsigned int i = 0; i < (fractionSize - byteCount); i++) fractionContainer.push_back(0);
}

template<int fraction, int exponent>
VariableFloat<fraction, exponent> operator + (const VariableFloat<fraction, exponent> &n1, const VariableFloat<fraction, exponent> &n2)
{
    VariableFloat<fraction, exponent> ret(0.0);
    std::vector<u_char> retExponent;

    bool sameSigns = n1.getSign() == n2.getSign();

    //|n1| > |n2|
    ret.setSign(n1.getSign());
    std::vector<u_char> sub = n1.getExponentContainer();
    retExponent = n1.getExponentContainer();
    std::vector<u_char> higherFrac = n1.getFractionContainer();
    std::vector<u_char> lowerFrac = n2.getFractionContainer();

    bool carry = ByteArray::subtractBytes(sub, n2.getExponentContainer());

    //|n2| > |n1|
    if (carry)
    {
        ret.setSign(n2.getSign());
        sub = n2.getExponentContainer();
        retExponent = n2.getExponentContainer();
        higherFrac = n2.getFractionContainer();
        lowerFrac = n1.getFractionContainer();
        ByteArray::subtractBytes(sub, n1.getExponentContainer());
    }

    //Add hidden '1'.
    higherFrac.push_back(0);
    ByteArray::shiftVectorRight(higherFrac, 1);
    ByteArray::setBit(higherFrac, 0, true);

    lowerFrac.push_back(0);
    ByteArray::shiftVectorRight(lowerFrac, 1);
    ByteArray::setBit(lowerFrac, 0, true);

    //Shift fraction for lower number.
    while (!ByteArray::checkIfZero(sub))
    {
        ByteArray::subtractBytes(sub, ByteArray::createOne(sub.size()));
        ByteArray::shiftVectorRight(lowerFrac, 1);
    }

    int pointPos = higherFrac.size()*8 - ByteArray::findHighestOrderOnePosition(higherFrac) - 1;

    //For overflow.
    if (sameSigns)
    {
        u_char carrySameSigns = ByteArray::addBytesEqualSize(higherFrac, lowerFrac);
        higherFrac.insert(higherFrac.begin(), carrySameSigns);
    }
    else
    {
        //There will be no overflow. 'higherFrac' is always bigger than 'lowerFrac'.
        ByteArray::subtractBytes(higherFrac, lowerFrac);
    }


    int newPointPos = higherFrac.size()*8 - ByteArray::findHighestOrderOnePosition(higherFrac) - 1;
    int shiftDirection = pointPos - newPointPos;
    if (shiftDirection < 0)
    {
        ByteArray::shiftVectorRight(higherFrac, -shiftDirection);
        ByteArray::addBytes(retExponent, ByteArray::createValue(retExponent.size(), -shiftDirection));
    }
    else
    {
        ByteArray::shiftVectorLeft(higherFrac, shiftDirection);
        ByteArray::subtractBytes(retExponent, ByteArray::createValue(retExponent.size(), shiftDirection));
    }

    //Remove what has been pushed before.
    higherFrac.erase(higherFrac.end() - 1);

    //Remove only if it was added in previous operations. (if same signs)
    if (sameSigns)
        higherFrac.erase(higherFrac.begin());

    //Shift back (remove leading '1').
    ByteArray::shiftVectorLeft(higherFrac, 1);
    ret.setExponentContainer(retExponent);
    ret.setFractionContainer(higherFrac);
    return ret;
}

template<int fraction, int exponent>
VariableFloat<fraction, exponent> operator - (const VariableFloat<fraction, exponent> &n1, const VariableFloat<fraction, exponent> &n2)
{
    VariableFloat<fraction, exponent> n2Bf = n2;
    n2Bf.setSign(!n2.getSign());
    return n1 + n2Bf;
}


template<int fraction, int exponent>
VariableFloat<fraction, exponent> operator * (const VariableFloat<fraction, exponent> &n1, const VariableFloat<fraction, exponent> &n2)
{
    VariableFloat<fraction, exponent> ret(0.0);

    //Prepare exponent.
    std::vector<u_char> retExponent = n1.getExponentContainer();
    ByteArray::subtractBytes(retExponent, n1.getBias());

    std::vector<u_char> secondExponent = n2.getExponentContainer();
    ByteArray::subtractBytes(secondExponent, n2.getBias());

    ByteArray::addBytes(retExponent, secondExponent);

    //If there is no more bits in fraction container.
    std::vector<u_char> retFraction = n1.getFractionContainer();

    //If there is no more bits in fraction container.
    std::vector<u_char> secondFraction = n2.getFractionContainer();

    secondFraction.push_back(0);
    ByteArray::shiftVectorRight(secondFraction,1);
    ByteArray::setBit(secondFraction, 0, true);

    retFraction.push_back(0);
    ByteArray::shiftVectorRight(retFraction,1);
    ByteArray::setBit(retFraction, 0, true);
    int pointPos = retFraction.size()*8 - ByteArray::findHighestOrderOnePosition(retFraction) - 1;

    //Multiply fractions.
    ByteArray::multiplyBytes(retFraction, secondFraction);

    //Set point at the same position in vector.
    ByteArray::shiftVectorRight(retFraction, pointPos);

    //Save fraction in ret object,
    //normalisation shift count.
    int shiftDirection = (signed)secondFraction.size()*8 - (signed)(retFraction.size() * 8 -
            ByteArray::findHighestOrderOnePosition(retFraction));

    //Compute exponent shift count and shift it accordingly.
    if (shiftDirection < 0)
    {
        ByteArray::shiftVectorRight(retFraction, -shiftDirection);
        //Create value only works for char so maximum shift count is 255.
        ByteArray::addBytes(retExponent, ByteArray::createValue(retExponent.size(), (-shiftDirection) & 0xFF));

    }
    else
    {
        ByteArray::shiftVectorLeft(retFraction, shiftDirection);
        ByteArray::subtractBytes(retExponent, ByteArray::createValue(retExponent.size(), (shiftDirection) & 0xFF));
    }

    //Remove extra bytes from ret vector.
    while (retFraction.size() != secondFraction.size())
        retFraction.erase(retFraction.begin());

    ByteArray::setBit(retFraction, 0, false);
    ByteArray::shiftVectorLeft(retFraction, 1);

    //Remove what has been added before shift.
    retFraction.erase(retFraction.end()-1);
    ByteArray::addBytes(retExponent, n1.getBias());
    ret.setExponentContainer(retExponent);
    ret.setFractionContainer(retFraction);
    return ret;
}

template<int fraction, int exponent>
VariableFloat<fraction, exponent> operator / (const VariableFloat<fraction, exponent> &n1, const VariableFloat<fraction, exponent> &n2)
{
    VariableFloat<fraction, exponent> returnNumber(0.0);
    bool resultSign = n1.getSign() != n2.getSign();

    //Check if any of the numbers is zero.
    if (n1.isZero())
    {
        if (n2.isZero())
        {
            returnNumber.setNan();
            return returnNumber;
        }
        else
        {
            returnNumber.setZero(resultSign);
            return returnNumber;
        }
    }
    else if (n2.isZero())
    {
        returnNumber.setInfinity(resultSign);
        return returnNumber;
    }

    //Subtract exponents.
    auto resultExponent = n1.getExponentContainer();
    auto secondExponent = n2.getExponentContainer();
    ByteArray::subtractBytes(secondExponent, n1.getBias());

    if (ByteArray::getBit(secondExponent, 0))
    {
        ByteArray::negateBytes(secondExponent);
        ByteArray::addBytes(resultExponent, secondExponent);
    }
    else ByteArray::subtractBytes(resultExponent, secondExponent);

    //Divide mantissas.
    auto resultMantissa = n1.getFractionContainer();
    auto secondMantissa = n2.getFractionContainer();

    //Add hidden '1'.
    resultMantissa.push_back(0);
    ByteArray::shiftVectorRight(resultMantissa, 1);
    ByteArray::setBit(resultMantissa, 0, true);

    secondMantissa.push_back(0);
    ByteArray::shiftVectorRight(secondMantissa, 1);
    ByteArray::setBit(secondMantissa, 0, true);
    ByteArray::divideBytes(resultMantissa, secondMantissa, fraction + 5);

    //Find highest order '1' of result mantissa, normalize it and remove leading '1'.
    int index = ByteArray::findHighestOrderOnePosition(resultMantissa);
    ByteArray::shiftVectorLeft(resultMantissa, index + 1);

    //Adjust result exponent.
    auto indexBytes = ByteArray::getBytesFromInt(index, resultExponent.size());
    bool overflow = ByteArray::subtractBytes(resultExponent, indexBytes);

    //Check for over or underflow.
    if (overflow)
    {
        returnNumber.setInfinity(resultSign);
        return returnNumber;
    }
    else if (ByteArray::compare(resultExponent, n1.getMinExponent()) == -1)
    {
        returnNumber.setSign(resultSign);
        return returnNumber;
    }

    //Save the result.
    returnNumber.setSign(resultSign);
    returnNumber.setExponentContainer(resultExponent);
    returnNumber.setFractionContainer(resultMantissa);
    return returnNumber;
}

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
    std::string currentFraction;
    std::string currentExponent;
    bool sign;

    str >> sign;
    str >> currentExponent;
    str >> currentFraction;
    obj = VariableFloat<fraction, exponent>(sign, currentExponent, currentFraction);
    return str;
}

template<int fraction, int exponent>
void VariableFloat<fraction,exponent>::printContainers(std::ostream &str) const
{
    //Write sign to output stream.
    if (sign) str << "- ";
    else str << "+ ";

    if (isInfinity()) str << "inf";
    else if (isNan()) str << "NaN";
    else
    {
        std::vector<u_char> copy(exponentContainer);

        if(!ByteArray::checkIfZero(exponentContainer))
            ByteArray::subtractBytes(copy, biasContainer);

        str << "0x";

        for (unsigned char i : copy)
        {
            str << std::hex << std::setfill('0') << std::setw(2) << (unsigned) i;
        }
        str << " ";

        str << "0x";
        for(unsigned char i : fractionContainer)
        {
            str << std::hex << std::setfill('0') << std::setw(2) << (unsigned) i;
        }
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
        auto byte = (u_char) strtol(stringByte.c_str(), nullptr, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

template<int fraction, int exponent>
int VariableFloat<fraction, exponent>::checkForOverflow(std::vector<u_char> &currentExponent)
{
    std::vector<u_char> temp = std::vector<u_char>(currentExponent);
    ByteArray::subtractBytes(temp, biasContainer);
    if (ByteArray::compare(temp, maxExponent) == 1) return 1;
    else if (ByteArray::compare(temp, minExponent) == -1) return -1;
    return 0;
}

template<int fraction, int exponent>
std::vector<u_char> &VariableFloat<fraction, exponent>::roundFraction(std::vector<u_char> &currentFraction)
{
    int rBitPosition = fraction;
    int arraySize = currentFraction.size() * 8;
    bool rBit = ByteArray::getBit(currentFraction, rBitPosition);
    bool sBit = false;

    //Check whether there are any '1's later in the fraction.
    for (int i = rBitPosition + 1; i < arraySize; ++i)
    {
        if (ByteArray::getBit(currentFraction, i))
        {
            sBit = true;
            break;
        }
    }

    //R = 1 and S = 1.
    if (rBit && sBit)
    {
        if (!ByteArray::getBit(currentFraction, fraction - 1))
        {
            ByteArray::setBit(currentFraction, fraction - 1, true);
            for (int i = fraction; i < arraySize; i++)
                ByteArray::setBit(currentFraction, i, false);
        }
        else
        {
            for (int i = fraction - 2; i >= 0; --i)
            {
                if (!ByteArray::getBit(currentFraction, i))
                {
                    ByteArray::setBit(currentFraction, i, true);
                    for (int j = i + 1; j < arraySize; j++)
                        ByteArray::setBit(currentFraction, j, false);
                    break;
                }
            }
        }
    }
    //R = 1 and S = 0.
    else if (rBit && !sBit)
    {
        if (ByteArray::getBit(currentFraction, fraction - 1))
        {
            for (int i = fraction - 2; i >= 0; --i)
            {
                if (!ByteArray::getBit(currentFraction, i))
                {
                    ByteArray::setBit(currentFraction, i, true);
                    for (int j = i + 1; j < arraySize; j++)
                        ByteArray::setBit(currentFraction, j, false);
                    break;
                }
            }
        }
        else
        {
            for (int i = fraction; i < arraySize; ++i)
                ByteArray::setBit(currentFraction, i, false);
        }
    }
    else
    {
        for (int i = fraction; i < arraySize; ++i)
            ByteArray::setBit(currentFraction, i, false);
    }
    return currentFraction;
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
bool VariableFloat<fraction, exponent>::isZero() const
{
    for (unsigned int i = 0; i < exponentContainer.size(); ++i)
    {
        if (exponentContainer[i] != 0)
            return false;
    }

    for (unsigned int i = 0; i < fractionContainer.size(); ++i)
    {
        if (fractionContainer[i] != 0)
            return false;
    }
    return true;
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

template<int fraction, int exponent>
std::string VariableFloat<fraction, exponent>::toBinary() const
{
    std::vector<u_char> exp = getExponentContainer();
    ByteArray::subtractBytes(exp, biasContainer);

    std::vector<u_char> frac = getFractionContainer();
    frac.push_back(0);
    ByteArray::shiftVectorRight(frac,1);
    ByteArray::setBit(frac, 0, true);

    int pointPos = 1;
    while (!ByteArray::checkIfZero(exp))
    {
        pointPos ++;
        ByteArray::subtractBytes(exp, ByteArray::createOne(exp.size()));
    }
    return (!getSign() ? "+ ":"- ") + ByteArray::toBinaryString(frac, pointPos);
}

template<int fraction, int exponent>
void VariableFloat<fraction, exponent>::setZero(bool setSign)
{
    sign = setSign;
    for (int i = 0; i < exponentSize; ++i) exponentContainer[i] = 0;
    for (int i = 0; i < fractionSize; ++i) fractionContainer[i] = 0;
}

template<int fraction, int exponent>
void VariableFloat<fraction, exponent>::setInfinity(bool setSign)
{
    sign = setSign;
    for (unsigned int i = 0; i < exponentSize; ++i) exponentContainer[i] = 255;
    for (unsigned int i = 0; i < fractionSize; ++i) fractionContainer[i] = 0;
}

template<int fraction, int exponent>
void VariableFloat<fraction, exponent>::setNan()
{
    for (int i = 0; i < exponentSize; ++i) exponentContainer[i] = 255;
    fractionContainer[0] = 255;
}
