TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    VariableFloat.h \
    Timer.h \
    ByteArray.h \
    Test.h \
    AddingTest.h

SOURCES += \
    main.cpp \
    Timer.cpp \
    ByteArray.cpp \
    Test.cpp \
    AddingTest.cpp
