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
    test/DevTest.h \
    test/AddTest.h

SOURCES += \
    main.cpp \
    util/Timer.cpp \
    ByteArray.cpp \
    test/Test.cpp \
    test/SubTest.cpp \
    test/MulTest.cpp \
    test/DevTest.cpp \
    test/AddTest.cpp
