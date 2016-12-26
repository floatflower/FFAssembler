#include <QStringList>
#include <QChar>
#include <QDebug>
#include <QString>

#include "Source/Instruction/instruction.h"

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

QString Instruction::leftTarget ( void )
{
    return m_leftTarget ;
}
QString Instruction::rightTarget ( void )
{
    return m_rightTarget ;
}

int Instruction::size ( void )
{
    return m_size ;
}

int Instruction::location ( void )
{
    return m_location ;
}

int Instruction::lineNumber ( void )
{
    return m_lineNumber ;
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
    QStringList temp_targetList = target.split( QChar( ',' ) , QString::SkipEmptyParts ) ;
    if ( temp_targetList.size() == 2 )
    {
        m_leftTarget = temp_targetList.at ( 0 ) ;
        m_rightTarget = temp_targetList.at ( 1 ) ;
    }
    else if ( temp_targetList.size() == 1 )
    {
        m_leftTarget = temp_targetList.at(0) ;
    }
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

void Instruction::setLineNumber ( int lineNumber )
{
    m_lineNumber = lineNumber ;
}

QBitArray* Instruction::operandBit ( void )
{
    return m_operandBit ;
}

QBitArray* Instruction::targetBit ( void )
{
    return m_targetBit ;
}

QBitArray* Instruction::flagBit ( void )
{
    return m_flagBit ;
}

void Instruction::setOperand( QBitArray* operand )
{
    m_operandBit = operand ;
}

void Instruction::setTarget( QBitArray* target )
{
    m_targetBit = target ;
}

void Instruction::setFlag( QBitArray* flag )
{
    m_flagBit = flag ;
}

void Instruction::setSingleFlag ( int position , bool bit )
{
    m_flagBit -> setBit( position , bit ) ;
}
