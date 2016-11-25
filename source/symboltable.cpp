#include <QDebug>
#include <QHash>

#include "symboltable.h"

SymbolTable::SymbolTable(QObject *parent)
    : QObject(parent)
{

}

void SymbolTable::insertSymbol ( QString symbol , int size , int lineNumber , int location )
{
    if ( ! contains ( symbol ) )
    {
        insert ( symbol , location ) ;
    }
    else
    {
        qDebug () << "[Error] At line"
                  << lineNumber
                  << ": Symbol :"
                  << symbol
                  << "is exist." ;
    }
}

void SymbolTable::symbolTableTest ( void )
{
    for ( QHash::iterator it_symbolTable = begin ( ) ;
          it_symbolTable != end ( ) ;
          it_symbolTable ++ )
    {
        qDebug () << "Symbol :"
                  << it_symbolTable.key()
                  << "Location :"
                  << it_symbolTable.value() ;
    }
}
