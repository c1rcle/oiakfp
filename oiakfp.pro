TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    VariableFloat.h \
    util/Timer.h \
    ByteArray.h \
    test/Test.h \
    test/SubTest.h \
    test/MulTest.h \
    test/AddTest.h \
    test/DivTest.h

SOURCES += \
    main.cpp \
    util/Timer.cpp \
    ByteArray.cpp \
    test/Test.cpp \
    test/SubTest.cpp \
    test/MulTest.cpp \
    test/AddTest.cpp \
    test/DivTest.cpp
