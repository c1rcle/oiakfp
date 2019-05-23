cmake_minimum_required(VERSION 3.13)
project(Projekt)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projekt main.cpp VariableFloat.h ByteArray.h ByteArray.cpp util/Timer.h util/Timer.cpp test/AddTest.h test/SubTest.h test/MulTest.h test/DivTest.h test/Test.h test/Test.cpp)