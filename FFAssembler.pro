QT += core
QT -= gui

CONFIG += c++11

TARGET = ff
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += source/main.cpp \
    source/commandhandler.cpp \
    source/ffassembler.cpp \
    source/passone.cpp \
    source/instruction.cpp

HEADERS += \
    source/commandhandler.h \
    source/ffassembler.h \
    source/passone.h \
    source/instruction.h
