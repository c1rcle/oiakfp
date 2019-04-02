#include <iostream>
#include <Float.h>

#include <vector>
using namespace std;


void test(){

    Float<23,8> f(-1.001f);
    f.printContainers(cout);

}


int main(int argc, char *argv[])
{



    test();
    return 0;

}
