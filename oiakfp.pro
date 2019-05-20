TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    VariableFloat.h \
    Timer.h \
    ByteArray.h \
    Test.h \
    SubTest.h \
    MulTest.h \
    DevTest.h \
    AddTest.h

SOURCES += \
    main.cpp \
    Timer.cpp \
    ByteArray.cpp \
    Test.cpp \
    SubTest.cpp \
    MulTest.cpp \
    DevTest.cpp \
    AddTest.cpp
