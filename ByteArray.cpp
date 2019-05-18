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

bool ByteArray::addBytesEqSize(std::vector<u_char> &first, const std::vector<u_char> &second)
{
    u_char carry = 0;
    for(int i=first.size()-1;i>=0;--i){
        short part= first[i] + second[i] + carry;
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
    auto * s = (u_char*) &second;
    std::vector<u_char> res = first;

    bool carry = subtractBytes(res, second);
    return checkIfZero(res);
}

bool ByteArray::checkIfZero(const std::vector<u_char> &first)
{
    for (u_char i : first)
    {
        if (i != 0) return false;
    }
    return true;
}

std::vector<u_char> ByteArray::createOne(unsigned int size)
{
    std::vector<u_char> ret(size);
    ret[ret.size()-1] = 0x1;
    return ret;
}

std::vector<u_char> ByteArray::createValue(unsigned int size, u_char value)
{
    std::vector<u_char> ret(size);
    ret[ret.size()-1] = value;

    return ret;
}

void ByteArray::multiplyBytes(std::vector<u_char> &first, const std::vector<u_char> &second)
{
    std::vector<std::vector<u_char> > partSums;

    //multiply first by each byte of second
    for (u_char i : second)
    {
        std::vector<u_char> partSum = first;
        multiplyBytesByByte(partSum, i);
        partSums.push_back(partSum);
    }

    //calculate size of part sums
    unsigned int sizeF = first.size();
    unsigned int sizeS = second.size();
    unsigned int size = sizeF + sizeS - 1;

    //make all part sums equal size
    for (unsigned int i = 0; i < partSums.size(); ++i)
    {
        for (unsigned int j = 0; j < i; ++j)
            partSums[i].push_back(0);

        for (unsigned int j = i; partSums[i].size() <= size; ++j)
            partSums[i].insert(partSums[i].begin(), 0);
    }

    first = partSums[0];
    u_char carryover = 0; //sums of all carry
    for (unsigned int i = 1; i < partSums.size(); ++i)
        if (addBytesEqSize(first, partSums[i])) carryover++;

    //if range has to be extended
    if (carryover > 0) first.insert(first.begin(), carryover);
    //std::cout<<partSums<<std::endl;
}

void ByteArray::multiplyBytesByByte(std::vector<u_char> &first, u_char multiplier)
{
    u_char carry = 0;
    for (int i = first.size() - 1; i >= 0; --i)
    {
        unsigned short part = first[i] * multiplier;
        first[i] = (part & 0xFF) + carry;
        carry = part >> 8;
    }
    if (carry > 0) first.insert(first.begin(), carry);
}

unsigned int ByteArray::findOldestOnePostition(const std::vector<u_char> &first)
{
    unsigned int ret = 0;
    for (unsigned int i=0;i<=first.size();++i)
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
//    /ret = first.size() * 8 - ret;
    return ret;
}

unsigned int ByteArray::cutVector(std::vector<u_char> &first, unsigned int sizeInBits)
{
    for(unsigned int i = first.size()-1;i>=0;--i)
    {

    }
    std::vector<u_char> data;

    for(unsigned int i = first.size()-1;i>=0;--i){
        if(sizeInBits >= 8);
    }
}

std::ostream& operator <<(std::ostream& str, const std::vector<u_char>& obj)
{
    for (const u_char i : obj) str << std::hex << "0x" << (unsigned) i << " ";
    return str;
}

std::ostream &operator <<(std::ostream &str, const std::vector<std::vector<u_char> > &obj)
{
    for (const auto & i : obj) str << i << std::endl;
    return str;
}
