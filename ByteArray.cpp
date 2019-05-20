#include "ByteArray.h"

void ByteArray::putBytes(const u_char * source, u_int size, std::vector<u_char> &destination)
{
    for (unsigned int i = 0; i < size; ++i)
        destination.insert(destination.begin(), source[i]);
}

void ByteArray::setBit(std::vector<u_char> &array, u_int position, bool value)
{
    int bytePosition = position / 8;
    int bitPosition = position % 8;

    u_char mask = 0x80;
    mask >>= bitPosition;

    if (value) array[bytePosition] |= mask;
    else array[bytePosition] &= (~mask);
}


bool ByteArray::getBit(std::vector<u_char> &array, u_int position)
{
    int bytePosition = position / 8;
    int bitPosition = position % 8;
    return (array[bytePosition] >> (8 - bitPosition - 1)) & 0x01;
}

void ByteArray::shiftVectorRight(std::vector<u_char> &vector, int shift)
{
    int size = (unsigned) vector.size() * 8;
    int s1 = shift;

    for(int i = size - 1; i >= s1; --i)
        setBit(vector, i, getBit(vector, i - shift));
    for(int i = s1 - 1; i >= 0; --i)
        setBit(vector, i, false);
}


void ByteArray::shiftVectorLeft(std::vector<u_char> &vector, int shift)
{
    int size = (unsigned) vector.size() * 8;
    int s1 = size - shift;

    for (int i = 0; i < s1; ++i)
        setBit(vector, i, getBit(vector, i + shift));
    for (int i = s1; i < size; ++i)
        setBit(vector, i, false);
}

std::vector<u_char> ByteArray::getBytesFromInt(unsigned int value, unsigned int size)
{
    auto result = std::vector<u_char>();
    for (int i = 0; i < 4; ++i)
    {
        u_char byte = value & 0xFF;
        result.insert(result.begin(), byte);
        value >>= 8;
    }

    if (size > 4)
    {
        int difference = size - 4;
        for (int i = 0; i < difference; ++i) result.insert(result.begin(), 0);
    }
    else if (size < 4)
    {
        int difference = 4 - size;
        for (int i = 0; i < difference; ++i) result.erase(result.begin());
    }
    return result;
}

bool ByteArray::addBytes(std::vector<u_char> &first, const std::vector<u_char> &second)
{
    u_char partialProduct = 0;
    int firstSize = first.size() - 1;
    int secondSize = second.size() - 1;
    int lastIndex = 0;
    bool carry = false;

    for (int i = 0; i <= secondSize; ++i)
    {
        partialProduct = first[firstSize - i] + second[secondSize - i];
        if (carry) partialProduct++;
        carry = partialProduct < first[firstSize - i];
        first[firstSize - i] = partialProduct;
        lastIndex = firstSize - i;
        if (firstSize - i < 0) break;
    }
    while (carry && lastIndex > 0)
    {
        partialProduct = first[lastIndex] + 1;
        carry = partialProduct < first[lastIndex];
        lastIndex--;
    }
    return carry;
}

u_char ByteArray::addBytesEqualSize(std::vector<u_char> &first, const std::vector<u_char> &second)
{
    u_char carry = 0;
    for (int i = first.size() - 1; i >= 0 ; --i)
    {
        short part = first[i] + second[i] + carry;
        first[i] = part & 0xFF;
        carry = part >> 8;
    }
    return carry;
}

bool ByteArray::subtractBytes(std::vector<u_char> &first, const std::vector<u_char> &second)
{
    u_char partialProduct = 0;
    int firstSize = first.size() - 1;
    int secondSize = second.size() - 1;
    int lastIndex = 0;
    bool carry = false;

    for (int i = 0; i <= secondSize; ++i)
    {
        partialProduct = first[firstSize - i] - second[secondSize - i];
        if (carry) partialProduct--;
        carry = partialProduct > first[firstSize - i];
        first[firstSize - i] = partialProduct;
        lastIndex = firstSize - i;
        if (firstSize - i < 0) break;
    }
    while (carry && lastIndex > 0)
    {
        partialProduct = first[lastIndex] - 1;
        carry = partialProduct > first[lastIndex];
        lastIndex--;
    }
    return carry;
}

int ByteArray::compare(const std::vector<u_char> &first, const std::vector<u_char> &second)
{
    //TODO - clean function cause it has unused local variables.
    auto * s = (u_char*) &second;
    std::vector<u_char> res = first;

    bool carry = subtractBytes(res, second);
    return checkIfZero(res);
}

bool ByteArray::checkIfZero(const std::vector<u_char> &first)
{
    for (u_char i : first)
        if (i != 0) return false;
    return true;
}

std::vector<u_char> ByteArray::createOne(unsigned int size)
{
    std::vector<u_char> ret(size);
    ret[ret.size() - 1] = 0x1;
    return ret;
}

std::vector<u_char> ByteArray::createValue(unsigned int size, u_char value)
{
    std::vector<u_char> ret(size);
    ret[ret.size() - 1] = value;
    return ret;
}

void ByteArray::multiplyBytes(std::vector<u_char> &first, const std::vector<u_char> &second)
{
    std::vector<std::vector<u_char>> partSums;

    //Multiply first by each byte of second.
    for (int i = second.size() - 1; i >= 0; --i)
    {
        std::vector<u_char> partSum = first;
        multiplyBytesByByte(partSum, second[i]);
        partSums.push_back(partSum);
    }

    //Calculate size of partial sums.
    unsigned int sizeF = first.size();
    unsigned int sizeS = second.size();
    unsigned int size = sizeF + sizeS - 1;

    //Make all part sums equal size.
    for (unsigned int i = 0; i < partSums.size(); ++i)
    {
        for (unsigned int j = 0; j < i; ++j)
            partSums[i].push_back(0);

        for (unsigned int j = i; partSums[i].size() <= size; ++j)
            partSums[i].insert(partSums[i].begin(), 0);
    }

    first = partSums[0];
    u_char carryover = 0; //Sum of all carry occurrences.
    for (unsigned int i = 1; i < partSums.size(); ++i)
        if (addBytesEqualSize(first, partSums[i])) carryover++;

    //If range has to be extended.
    if (carryover > 0) first.insert(first.begin(), carryover);
}

void ByteArray::multiplyBytesByByte(std::vector<u_char> &first, u_char multiplier)
{
    u_char carry = 0;
    for (int i = first.size() - 1; i >= 0; --i)
    {
        unsigned short part = first[i] * multiplier + carry;
        first[i] = (part & 0xFF);
        carry = part >> 8;
    }
    if (carry > 0) first.insert(first.begin(), carry);
}

void ByteArray::divideBytes(std::vector<u_char> &first, const std::vector<u_char> &second, unsigned int precision)
{
    int byteCount = (precision - 1) / 8 + 1;
    auto result = std::vector<u_char>(byteCount, 0);

    auto quotient = first;
    auto divisor = second;
    for (int i = 0; i < byteCount; ++i)
    {
        quotient.insert(quotient.begin(), 0);
        divisor.insert(divisor.begin(), 0);
    }
    auto partialProduct = std::vector<u_char>(quotient.size(), 0);
    int bitCount = quotient.size() * 8;

    for (int i = 0; i < precision; ++i)
    {
        for (int j = bitCount - 1; j >= 0; --j)
        {
            bool shiftBit = getBit(quotient, 0);
            shiftVectorLeft(partialProduct, 1);
            shiftVectorLeft(quotient, 1);
            setBit(partialProduct, bitCount - 1, shiftBit);

            auto temp = partialProduct;
            if (subtractBytes(partialProduct, divisor))
            {
                setBit(quotient, bitCount - 1, false);
                partialProduct = temp;
            }
            else setBit(quotient, bitCount - 1, true);
        }

        setBit(result, i, getBit(quotient, bitCount - 1));
        quotient = partialProduct;
        shiftVectorLeft(quotient, 1);
        for (int k = 0; k < quotient.size(); ++k) partialProduct[k] = 0;
    }
    first = result;
}

unsigned int ByteArray::findHighestOrderOnePosition(const std::vector<u_char> &first)
{
    unsigned int ret = 0;
    for (unsigned int i = 0; i <= first.size(); ++i)
    {
        if (first[i] == 0)
        {
            ret += 8;
            continue;
        }
        else if(first[i] & 0x80) ret += 0;
        else if(first[i] & 0x40) ret += 1;
        else if(first[i] & 0x20) ret += 2;
        else if(first[i] & 0x10) ret += 3;
        else if(first[i] & 0x8) ret += 4;
        else if(first[i] & 0x4) ret += 5;
        else if(first[i] & 0x2) ret += 6;
        else if(first[i] & 0x1) ret += 7;
        break;
    }
    return ret;
}

unsigned int ByteArray::findLowestOrderOnePosition(std::vector<u_char> &first)
{
    for (int i = first.size() * 8 - 1; i >= 0; --i)
    {
        if (getBit(first, i)) return i;
    }
    return -1;
}

std::vector<u_char> ByteArray::cutVector(std::vector<u_char> &first, unsigned int sizeInBits)
{
    int byteSize = (sizeInBits - 1) / 8 + 1;
    auto result = std::vector<u_char>(byteSize, 0);
    for (int i = 0; i < sizeInBits; ++i)
        setBit(result, i, getBit(first, i));
    return result;
}

std::string ByteArray::toBinaryString(const std::vector<u_char> &first, unsigned point)
{
    std::string ret;
    for (int i = 0; i <= first.size(); ++i)
    {
        u_char mask = 0x80;
        for (int j = 7; j >= 0; --j)
        {
            //std::cout<<j<<", "<<i<<", "<<std::hex<<(unsigned int)mask<<", "<<std::hex<<(unsigned int)first[i]<<", "<<(first[i]&mask)<<std::endl;
            ret += (first[i] & mask) == 0 ? '0' : '1';
            mask = mask >> 1;
        }
    }
    ret.insert(ret.begin() + point, '.');
    return ret;
}

std::ostream &operator <<(std::ostream& str, const std::vector<u_char>& obj)
{
    for (const u_char i : obj) str << std::hex << "0x" << (unsigned) i << " ";
    return str;
}

std::ostream &operator <<(std::ostream &str, const std::vector<std::vector<u_char>> &obj)
{
    for (const auto & i : obj) str << i << std::endl;
    return str;
}