#include <iostream>
#include <iomanip>
#include "VariableFloat.h"

#include "Timer.h"

using namespace std;



void shiftTest()
{
    //std::vector<u_char> bytes = {0x11, 0x2, 0x3, 0x4, 0x5, 0x6};
    std::vector<u_char> bytes = {0xFF,0xFF,0xFF,0xFF};

//    std::cout<<bytes<<std::endl;
//    f.shiftVectorRight(bytes, 9);
//    std::cout<<bytes<<std::endl;


    Timer t1;
    t1.start();

   for(unsigned int i=0;i<=bytes.size()*8;++i){
        std::vector<u_char> buf = bytes;
        ByteArray::shiftVectorRight(buf, i);

        //std::cout<<std::chrono::duration_cast<double, std::chrono::microseconds>
        //           (std::chrono::high_resolution_clock::now() - t1)<<std::endl;
        //std::cout<<bytes<<std::endl;
        //f.setBit(bytes[1], 1, 0);
        //std::cout<<buf<<std::endl;
   }
   t1.stop();
   std::cout<<t1.elapsed()<<std::endl;


}
void ifzeroTest()
{
    std::vector<u_char> buf = {0x0,0x0,0x0};
    std::cout<<ByteArray::checkIfZero(buf)<<std::endl;
}

int main()
{

    shiftTest();

    VariableFloat<26, 10> f(0.0f);
    std::cout << f << std::endl;

    //TODO:
    //VariableFloat<26, 10> g(0.0f);
    //std::cout << g << std::endl;
    VariableFloat<68, 14> d(2.0f);
    std::cout << d << std::endl;
    return 0;
}
