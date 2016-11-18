#include "instruction.h"

Instruction::Instruction(QObject *parent) : QObject(parent)
{

}

QString Instruction::symbol ( void )
{
    return m_symbol ;
}

QString Instruction::operand ( void )
{
    return m_operand ;
}

QString Instruction::target ( void )
{
    return m_target ;
}

void Instruction::setSymbol ( QString symbol )
{
    m_symbol = symbol ;
}

void Instruction::setOperand ( QString operand )
{
    m_operand = operand ;
}

void Instruction::setTarget ( QString target )
{
    m_target = target ;
}
