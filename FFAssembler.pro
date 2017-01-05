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
    Source/PassTwo/sicgencodepure.cpp \
    Source/Table/symboltablewithbit.cpp \
    Source/Instruction/instructionformat1.cpp \
    Source/Instruction/instructionformat2.cpp \
    Source/Instruction/instructionformat4.cpp \
    Source/Instruction/instructionformat3.cpp \
    Source/Instruction/variable.cpp \
    Source/Instruction/assemblydirective.cpp \
    Source/Exception/exception.cpp \
    Source/Exception/syntaxexception.cpp \
    Source/PassTwo/sicxegencodewithorigin.cpp \
    Source/Table/registertable.cpp \
    Source/PassTwo/sicxegencodepure.cpp

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
    Source/PassTwo/sicgencodepure.h \
    Source/Table/symboltablewithbit.h \
    Source/Instruction/instructionformat1.h \
    Source/Instruction/instructionformat2.h \
    Source/Instruction/instructionformat4.h \
    Source/Instruction/instructionformat3.h \
    Source/Instruction/variable.h \
    Source/Instruction/assemblydirective.h \
    Source/Exception/exception.h \
    Source/Exception/syntaxexception.h \
    Source/PassTwo/sicxegencodewithorigin.h \
    Source/Table/registertable.h \
    Source/PassTwo/sicxegencodepure.h
