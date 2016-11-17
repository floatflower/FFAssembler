QT += core
QT -= gui

CONFIG += c++11

TARGET = ff
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    commandhandler.cpp \
    ffassembler.cpp

HEADERS += \
    commandhandler.h \
    ffassembler.h
