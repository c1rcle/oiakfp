#include "ByteArray.h"

void ByteArray::putBytes(const u_char * source, u_int size, std::vector<u_char> &destination)
{
    for (unsigned int i = 0; i < size; ++i)
        destination.insert(destination.begin(), source[i]);
}

void ByteArray::setBit(u_char &byte, u_int position, bool value)
{
    char mask = 1;
    mask <<= position;

    if (value) byte |= mask;
    else byte &= (~mask);
}


bool ByteArray::getBit(u_char &byte, u_int position)
{
    return (byte >> position) & 0x1;
}

void ByteArray::shiftVectorRight(std::vector<u_char> &vector, int shift)
{
    int byteOffset = shift / 8;
    int bitOffset = shift % 8;

    int size = (unsigned)vector.size()*8;
    int s1 = size - shift;

    for (int i = 0; i < s1; ++i){
        //std::cout<<i<<" "<<vector<<std::endl;
        setBit(vector[vector.size()- i/8 -1],i%8, getBit(vector[vector.size()- (i+bitOffset)/8 - byteOffset -1], (i+bitOffset)%8));
    }
    for (int i = s1; i < size; ++i)
        setBit(vector[vector.size()- i/8 -1],i%8,0);
}


void ByteArray::shiftVectorLeft(std::vector<u_char> &vector, int shift)
{
    int byteOffset = shift / 8;
    int bitOffset = shift % 8;

    int size = (unsigned)vector.size() * 8;
    int s1 = shift;

    for(int i=size-1;i>=s1;--i){
        //std::cout<<vector.size()- i/8 -1<<":"<<i%8<<" <- "<<vector.size()- (i-bitOffset)/8 + byteOffset -1<<":"<<(i-bitOffset)%8<<std::endl;
        setBit(vector[vector.size()- i/8 -1],i%8, getBit(vector[vector.size()- (i-bitOffset)/8 + byteOffset -1], (i-bitOffset)%8));
    }

    for(int i=s1-1;i>=0;--i){
        setBit(vector[vector.size()- i/8 -1],i%8,0);
    }
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
    for(u_char i:first)
    {
        if(i != 0) return false;
    }
    return true;
}

std::vector<u_char> ByteArray::createOne(unsigned int size)
{
    std::vector<u_char> ret(size);
    ret[ret.size()-1] = 0x1;

    return ret;
}

std::ostream& operator <<(std::ostream& str, const std::vector<u_char>& obj)
{
    for(const u_char i : obj)
    {
        str<<std::hex<<"0x"<<(unsigned)i<<" ";
    }
    return str;
}
