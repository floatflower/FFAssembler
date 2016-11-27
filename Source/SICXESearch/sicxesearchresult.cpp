#include "Source/SICXESearch/sicxesearchresult.h"

SICXESearchResult::SICXESearchResult(QObject *parent) : QObject(parent)
{

}
void SICXESearchResult::setType ( int type )
{
    m_type = type ;
}

void SICXESearchResult::setSize ( int size )
{
    m_size = size ;
}

int SICXESearchResult::type ( void )
{
    return m_type ;
}

int SICXESearchResult::size ( void )
{
    return m_size ;
}
