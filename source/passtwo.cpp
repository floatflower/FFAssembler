#include "passtwo.h"

PassTwo::PassTwo(QObject *parent) : QObject(parent)
{

}

void PassTwo::setInstructionSet ( InstructionSet *instructionSet )
{
    m_instructionSet = instructionSet ;
}

void PassTwo::setTableHandler ( TableHandler *tableHandler )
{
    m_tableHandler = tableHandler ;
}
