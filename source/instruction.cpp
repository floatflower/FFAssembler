#include "instruction.h"

Instruction::Instruction(QObject *parent)
    : QObject(parent),
      m_symbol("") ,
      m_operand("") ,
      m_target("") ,
      m_size(0) ,
      m_location(0)
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

int Instruction::size ( void )
{
    return m_size ;
}

int Instruction::location ( void )
{
    return m_location ;
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

void Instruction::setSize ( int size )
{
    m_size = size ;
}

void Instruction::setLocation ( int location )
{
    m_location = location ;
}
