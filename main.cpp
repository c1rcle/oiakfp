#include <iostream>
#include <iomanip>
#include "VariableFloat.h"

using namespace std;

std::ostream& operator <<(std::ostream& str, const std::vector<u_char>& obj)
{
    for(const u_char i : obj)
    {
        str<<std::hex<<"0x"<<(unsigned)i<<" ";
    }
    return str;
}

void shiftTest()
{
    VariableFloat<26, 10> f(-18.47f);
    //std::vector<u_char> bytes = {0x11, 0x2, 0x3, 0x4, 0x5, 0x6};
    std::vector<u_char> bytes = {0xFF,0xFF,0xFF,0xFF};

//    std::cout<<bytes<<std::endl;
//    f.shiftVectorRight(bytes, 9);
//    std::cout<<bytes<<std::endl;


   for(int i=0;i<=bytes.size()*8;++i){
        std::vector<u_char> buf = bytes;
        f.shiftVectorRight(buf, i);
        //std::cout<<bytes<<std::endl;
        //f.setBit(bytes[1], 1, 0);
        std::cout<<buf<<std::endl;
    }


}

int main()
{

    shiftTest();
    return 0;

    VariableFloat<26, 10> f(-18.47f);
    std::cout << f << std::endl;
    VariableFloat<68, 14> d(19.23);
    std::cout << d << std::endl;
    return 0;
}
