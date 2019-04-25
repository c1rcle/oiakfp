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
public:

    /// Copies bytes to a container.
    /// \param source - source byte array.
    /// \param size - array element count.
    /// \param destination - destination vector.
    void putBytes(const u_char * source, u_int size, std::vector<u_char> &destination);

    /// Set specified bit value
    /// \param byte - byte to be set
    /// \param pos - position in range <0;7>
    /// \param value - new value
    ///
    void setBit(u_char& byte, u_int pos, bool value);

    ///
    /// \brief getBit get value of specified bit
    /// \param byte
    /// \param pos
    /// \return
    ///
    bool getBit(u_char& byte, u_int pos);

    /// Shifts a vector of bytes 'shift' times right.
    /// \param vector - vector which contents are going to be shifted.
    /// \param shift - bit shift count.
    void shiftVectorRight(std::vector<u_char> & vector, int shift);

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

    for (unsigned int i = 0; i < exponentSize; ++i) biasContainer.push_back(255);
    int shiftCount = exponentSize * 8 - (exponent - 1);
    shiftVectorRight(biasContainer, shiftCount);
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
    int byteCount = exponent >= FLOAT_EXPONENT ? (FLOAT_EXPONENT / 8) + 1 : exponentSize;
    putBytes(((u_char *)&floatExponent), byteCount, exponentContainer);
    for (unsigned int i = 0; i < (exponentSize - byteCount); i++) exponentContainer.insert(exponentContainer.begin(), 0);
    std::vector<u_char> floatBias = createBiasContainerForExponent(FLOAT_EXPONENT);
    subtractBytes(exponentContainer, floatBias);
    addBytes(exponentContainer, biasContainer);

    u_int floatFraction = floatBytes << (FLOAT_EXPONENT + 1);
    floatFraction >>= (FLOAT_EXPONENT + 1);
    byteCount = fraction >= FLOAT_FRACTION ? (FLOAT_FRACTION / 8) + 1: fractionSize;
    putBytes(((u_char *)&floatFraction), byteCount, fractionContainer);
    for (unsigned int i = 0; i < (fractionSize - byteCount); i++) fractionContainer.insert(fractionContainer.begin(), 0);

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
    int byteCount = exponent >= DOUBLE_EXPONENT ? (DOUBLE_EXPONENT / 8) + 1 : exponentSize;
    putBytes(((u_char *)&doubleExponent), byteCount, exponentContainer);
    for (unsigned int i = 0; i < (exponentSize - byteCount); i++) exponentContainer.insert(exponentContainer.begin(), 0);
    std::vector<u_char> doubleBias = createBiasContainerForExponent(DOUBLE_EXPONENT);
    subtractBytes(exponentContainer, doubleBias);
    addBytes(exponentContainer, biasContainer);

    u_int64_t doubleFraction = doubleBytes << (DOUBLE_EXPONENT + 1);
    doubleFraction >>= (DOUBLE_EXPONENT + 1);
    byteCount = fraction >= DOUBLE_FRACTION ? (DOUBLE_FRACTION / 8) + 1: fractionSize;
    putBytes(((u_char *)&doubleFraction), byteCount, fractionContainer);
    for (unsigned int i = 0; i < (fractionSize - byteCount); i++) fractionContainer.insert(fractionContainer.begin(), 0);

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
    for (unsigned int i = 0; i < exponentSize; ++i)
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

template<int fraction, int exponent>
void VariableFloat<fraction,exponent>::putBytes(const u_char * source, u_int size, std::vector<u_char> &destination)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        destination.insert(destination.begin(), source[i]);
    }
}

template<int fraction, int exponent>
void VariableFloat<fraction,exponent>::setBit(u_char &byte, u_int pos, bool value)
{
    char mask = 1;
    mask <<= pos;

    //std::cout<<std::hex<<(unsigned)mask<<std::endl;

    if(value){
        byte|=mask;
    }else{
        byte&=(~mask);
    }
}

template<int fraction, int exponent>
bool VariableFloat<fraction, exponent>::getBit(u_char &byte, u_int pos)
{
    return (byte >> pos) & 0x1;
}

template<int fraction, int exponent>
void VariableFloat<fraction, exponent>::shiftVectorRight(std::vector<u_char> &vector, int shift)
{
    int byteOffset = shift / 8;
    int bitOffset = shift % 8;

    int size = (unsigned)vector.size()*8;
    int s1 = size - shift;

    std::cout<<"shift:"<<s1<<" "<<size<<std::endl;

    for(int i=0;i<s1;++i){

        //std::cout<<i<<". dst:"<<vector.size()- i/8 -1<<" b:"<<i%8<<", src: "<<vector.size()- i/8 - byteOffset -1<<" b:"<<(i+bitOffset)%8<<std::endl;


        setBit(vector[vector.size()- i/8 -1],i%8, getBit(vector[vector.size()- i/8 - byteOffset -1], (i+bitOffset)%8));
    }

    for(int i=s1;i<size;++i){
        setBit(vector[vector.size()- i/8 -1],i%8,0);
    }


    /*
     this iteration is correct if Big Endian is used.
    */
    /*for(int i=0;i<s1;++i){
        setBit(vector[i/8],i%8, getBit(vector[i/8+byteOffset], (i+bitOffset)%8));
    }

    for(int i=s1;i<size;++i)
        setBit(vector[i/8],i%8,0);*/
}

template<int fraction, int exponent>
std::vector<u_char> VariableFloat<fraction, exponent>::createBiasContainerForExponent(int customExponent)
{
    std::vector<u_char> customBias;
    int customExponentSize = (customExponent / 8) + 1;
    customBias.reserve(customExponentSize);
    for (int i = 0; i < customExponentSize; ++i) customBias.push_back(255);

    int shiftCount = customExponentSize * 8 - (customExponent - 1);
    shiftVectorRight(customBias, shiftCount);
    return customBias;
}

template<int fraction, int exponent>
bool VariableFloat<fraction, exponent>::addBytes(std::vector<u_char> &first, std::vector<u_char> &second)
{
    u_char partialProduct = 0;
    int firstSize = first.size() - 1;
    int secondSize = second.size() - 1;
    bool carry = false;
    for (int i = 0; i <= secondSize; ++i)
    {
        partialProduct = first[firstSize - i] + second[secondSize - i];
        if (carry) partialProduct++;
        carry = partialProduct < first[firstSize - i];
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
    for (int i = 0; i <= secondSize; ++i)
    {
        partialProduct = first[firstSize - i] - second[secondSize - i];
        if (carry) partialProduct--;
        carry = partialProduct > first[firstSize - i];
        first[firstSize - i] = partialProduct;
    }
    return carry;
}
