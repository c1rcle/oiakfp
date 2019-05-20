cmake_minimum_required(VERSION 3.13)
project(Projekt)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projekt main.cpp VariableFloat.h ByteArray.h ByteArray.cpp util/Timer.h util/Timer.cpp test/AddTest.h test/AddTest.cpp test/SubTest.h test/SubTest.cpp test/MulTest.h test/MulTest.cpp test/DivTest.h test/DivTest.cpp test/Test.h test/Test.cpp)