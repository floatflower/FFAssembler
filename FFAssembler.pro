QT += core
QT -= gui

CONFIG += c++11

TARGET = ff
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += Source/main.cpp \
    Source/commandhandler.cpp \
    Source/ffassembler.cpp \
    Source/PassOne/passone.cpp \
    Source/Instruction/instruction.cpp \
    Source/Instruction/instructionset.cpp \
    Source/SICXESearch/sicxesearch.cpp \
    Source/SICXESearch/sicxesearchresult.cpp \
    Source/globalutility.cpp \
    Source/Table/symboltable.cpp \
    Source/Table/tablehandler.cpp \
    Source/PassTwo/passtwo.cpp \
    Source/PassTwo/sicgencodewithorigin.cpp \
    Source/PassTwo/sicgencodepure.cpp

HEADERS += \
    Source/commandhandler.h \
    Source/ffassembler.h \
    Source/PassOne/passone.h \
    Source/Instruction/instruction.h \
    Source/Instruction/instructionset.h \
    Source/SICXESearch/sicxesearch.h \
    Source/SICXESearch/sicxesearchresult.h \
    Source/globalutility.h \
    Source/Table/symboltable.h \
    Source/Table/tablehandler.h \
    Source/PassTwo/passtwo.h \
    Source/PassTwo/sicgencodewithorigin.h \
    Source/PassTwo/sicgencodepure.h
