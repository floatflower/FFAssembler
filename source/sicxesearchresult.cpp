#include "sicxesearchresult.h"

SICXESearchResult::SICXESearchResult(QObject *parent) : QObject(parent)
{

}
void SICXESearchResult::setType ( int type )
{
    m_type = type ;
}

void SICXESearchResult::setOpcode ( QBitArray opcode )
{
    m_opcode = opcode ;
}

void SICXESearchResult::setSize ( int size )
{
    m_size = size ;
}

int SICXESearchResult::type ( void )
{
    return m_type ;
}

QBitArray SICXESearchResult::opcode ( void )
{
    return m_opcode ;
}

int SICXESearchResult::size ( void )
{
    return m_size ;
}
