#include "ByteArray.h"

ByteArray::ByteArray()
{

}

void ByteArray::putBytes(const u_char * source, u_int size, std::vector<u_char> &destination)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        destination.insert(destination.begin(), source[i]);
    }
}


void ByteArray::setBit(u_char &byte, u_int pos, bool value)
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


bool ByteArray::getBit(u_char &byte, u_int pos)
{
    return (byte >> pos) & 0x1;
}


void ByteArray::shiftVectorRight(std::vector<u_char> &vector, int shift)
{
    int byteOffset = shift / 8;
    int bitOffset = shift % 8;

    int size = (unsigned)vector.size()*8;
    int s1 = size - shift;

    //std::cout<<"shift:"<<s1<<" "<<size<<std::endl;

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


void ByteArray::shiftVectorLeft(std::vector<u_char> &vector, int shift)
{
    int byteOffset = shift / 8;
    int bitOffset = shift % 8;

    int size = (unsigned)vector.size()*8;
    int s1 = size - shift;

}


bool ByteArray::addBytes(std::vector<u_char> &first, std::vector<u_char> &second)
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


bool ByteArray::subtractBytes(std::vector<u_char> &first, const std::vector<u_char> &second)
{
    u_char partialProduct = 0;
    int firstSize = first.size() - 1;
    int secondSize = second.size() - 1;
    bool carry = false;
    for (int i = 0; i <= secondSize; ++i)
    {
        //int buf = 0;
        //if(i < secondSize) buf = second[secondSize - i];
        //partialProduct = first[firstSize - i] - buf;
        partialProduct = first[firstSize - i] - second[secondSize - i];
        if (carry) partialProduct--;
        carry = partialProduct > first[firstSize - i];
        first[firstSize - i] = partialProduct;
    }
    return carry;
}

int ByteArray::compare(const std::vector<u_char> &first, const std::vector<u_char> &second)
{
    u_char* s = (u_char*)&second;
    std::vector<u_char> res = first;

    bool carry = subtractBytes(res, second);

    return checkIfZero(res);
}

bool ByteArray::checkIfZero(const std::vector<u_char> &first)
{
    for(u_char i:first){
        if(i != 0)
            return false;
    }

    return true;
}

/*std::ostream& operator <<(std::ostream& str, const std::vector<u_char>& obj)
{
    for(const u_char i : obj)
    {
        str<<std::hex<<"0x"<<(unsigned)i<<" ";
    }
    return str;
}*/
