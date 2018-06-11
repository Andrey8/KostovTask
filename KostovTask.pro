TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tests.cpp \
    shapes.cpp \
    shapeshelper.cpp

HEADERS += \
    container.h \
    tests.h \
    exception.h \
    base.h \
    shapes.h \
    shapeshelper.h
