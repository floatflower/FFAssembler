QT += core
QT -= gui

CONFIG += c++11

TARGET = ff
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += source/main.cpp \
    source/commandhandler.cpp \
    source/ffassembler.cpp

HEADERS += \
    source/commandhandler.h \
    source/ffassembler.h
