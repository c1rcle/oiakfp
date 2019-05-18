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

    /// Checks whether current exponent will lead to an overflow or underflow.
    /// \param currentExponent - current exponent byte container.
    /// \return 1 if overflow, -1 if underflow, otherwise 0.
    int checkForOverflow(std::vector<u_char> &currentExponent);

    /// Rounds the fraction using 'round to nearest' method.
    /// \param currentFraction - current fraction byte container.
    /// \return Reference to a modified byte container.
    std::vector<u_char> &roundFraction(std::vector<u_char> &currentFraction);
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

    /// Returns a reference to an object's fraction container.
    /// \return reference to an object's fraction container
    const std::vector<u_char>& getFractionContainer() const { return fractionContainer; }

    /// Returns a reference to an object's exponent container.
    /// \return reference to an object's exponent container
    const std::vector<u_char>& getExponentContainer() const { return exponentContainer; }

    /// Returns sign of a number.
    /// \return true if positive, otherwise false.
    bool getSign() const { return sign; }

    /// Sets fraction container using the argument's vector.
    /// \param f - container to be set.
    void setFractionContainer(const std::vector<u_char>& f) { fractionContainer = f; }

    /// Sets exponent container using the argument's vector.
    /// \param e - container to be set
    void setExponentContainer(const std::vector<u_char>& e) { exponentContainer = e; }

    /// Sets the sign of a number.
    /// \param s - sign to be set.
    void setSign(bool s) { sign = s; }
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
std::istream& operator>>(std::istream &str, VariableFloat<fraction, exponent> &obj);

template<int fraction, int exponent>
VariableFloat<fraction, exponent> operator + (const VariableFloat<fraction, exponent> &n1, const VariableFloat<fraction, exponent> &n2)
{
    VariableFloat<fraction, exponent> ret(0.0);
    std::vector<u_char> retExponent;

    bool sameSigns = n1.getSign() == n2.getSign();

    std::cout << "sizes: " << n1.getExponentContainer().size() << ", " <<
    n1.getFractionContainer().size() <<std::endl;

    //which number has bigger exponent
    n1.printContainers(std::cout);
    n2.printContainers(std::cout);

    //|n1| > |n2|

    ret.setSign(n1.getSign());
    std::vector<u_char> sub = n1.getExponentContainer();
    retExponent = n1.getExponentContainer();
    std::vector<u_char> higherFrac = n1.getFractionContainer();
    std::vector<u_char> lowerFrac = n2.getFractionContainer();

    bool carry = ByteArray::subtractBytes(sub, n2.getExponentContainer());
    std::cout << "sub: " << sub << " " << carry << "signs: " << sameSigns << std::endl;

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

    //remember to add 1 at the beginning of containers
    //higherFrac.insert(higherFrac.begin(), 0x1);
    //std::cout << "higher" << higherFrac << std::endl;


    std::cout << "(1) no hidden 1: " << higherFrac << std::endl;

    higherFrac.push_back(0);
    ByteArray::shiftVectorRight(higherFrac,1);
    ByteArray::setBit(higherFrac, 0, true);

    std::cout << "(1) hidden 1: " << higherFrac << std::endl;
    std::cout << "(2) no hidden 1: " << lowerFrac << std::endl;

    lowerFrac.push_back(0);
    ByteArray::shiftVectorRight(lowerFrac,1);
    ByteArray::setBit(lowerFrac, 0, true);
    std::cout << "(2) hidden 1: "  << lowerFrac << std::endl;

    //shift fraction for lower number
    while (!ByteArray::checkIfZero(sub))
    {
        //std::cout<<"iteration: "<<sub<<" "<<lowerFrac<<std::endl;
        ByteArray::subtractBytes(sub, ByteArray::createOne(sub.size()));
        std::cout << "i:" << lowerFrac << std::endl;
        ByteArray::shiftVectorRight(lowerFrac,1);
        std::cout << lowerFrac << std::endl;
    }

    if (sameSigns) ByteArray::addBytes(higherFrac, lowerFrac);
    else ByteArray::subtractBytes(higherFrac, lowerFrac);

    ByteArray::shiftVectorLeft(higherFrac,1);

    //normalisation
    //possible in both cases
    if (higherFrac[0] == 0x1) higherFrac.erase(higherFrac.begin());
    //possible when adding
    else if (higherFrac[0] > 0x1)
    {
        ByteArray::shiftVectorRight(higherFrac, 1);
        higherFrac.erase(higherFrac.begin());
        ByteArray::addBytes(retExponent, ByteArray::createOne(retExponent.size()));
    }
    //possible when subtracting
    else if (higherFrac[0] == 0x0)
    {
        std::cout << "subtracting " << higherFrac << std::endl;
        ByteArray::shiftVectorLeft(higherFrac,1);
        std::cout << "subtracting " << higherFrac << std::endl;
        higherFrac.erase(higherFrac.begin());
        ByteArray::subtractBytes(retExponent, ByteArray::createOne(retExponent.size()));
    }
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
    ByteArray::addBytes(retExponent, n2.getExponentContainer());

    //if there is no more bits in fraction container
    std::vector<u_char> retFraction = n1.getFractionContainer();

    std::cout << std::dec << (fraction+1 )<< " " << retFraction.size() << " " << retFraction.size() * 8 << std::endl;

    ByteArray::setBit(retFraction, fraction, true);

    //if there is no more bits in fraction container
    std::vector<u_char> secondFraction = n2.getFractionContainer();

    secondFraction.push_back(0);
    ByteArray::shiftVectorRight(secondFraction,1);
    ByteArray::setBit(secondFraction, 0, true);

    retFraction.push_back(0);
    ByteArray::shiftVectorRight(retFraction,1);
    ByteArray::setBit(retFraction, 0, true);


    std::cout << "multiplying" << std::endl;
    std::cout << "ret: " << retFraction << std::endl;
    std::cout << "sec: " << secondFraction << std::endl;

    //multiply fractions
    ByteArray::multiplyBytes(retFraction, secondFraction);

    //normalisation - TODO

    //save fraction in ret object
    int shiftDirection = (signed) ByteArray::findOldestOnePostition(retFraction) - fraction - 1; //normalisation shift count
    std::cout << "mul: " << retFraction << ", shift: " << std::dec << shiftDirection << ", " <<
    ByteArray::findOldestOnePostition(retFraction) << std::endl;

    //shift and shifts count to the exponent
    if (shiftDirection < 0)
    {
        ByteArray::shiftVectorLeft(retFraction, -shiftDirection);
        //crate value works only for char so maximum size of shifts is 255
        ByteArray::subtractBytes(retExponent, ByteArray::createValue(retExponent.size(), (-shiftDirection) & 0xFF));
    }
    else
    {
        ByteArray::shiftVectorRight(retFraction, shiftDirection);
        ByteArray::addBytes(retExponent, ByteArray::createValue(retExponent.size(), (shiftDirection) & 0xFF));
    }

    ret.setExponentContainer(retExponent);
    ret.setFractionContainer(retFraction);
    return ret;
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
    std::string frac;
    std::string exp;
    bool sign;

    str>>sign;
    str>>exp;
    str>>frac;


    obj = VariableFloat<fraction, exponent>(sign, exp, frac);

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
    for (unsigned int i = rBitPosition + 1; i < arraySize; ++i)
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
