#include <QDebug>
#include <QHash>
#include <QString>

#include "symboltable.h"

SymbolTable::SymbolTable(QObject *parent)
    : QObject(parent)
{

}

void SymbolTable::insertSymbol ( QString symbol , int lineNumber , int location )
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
    qDebug () << "SymbolTable : \n" ;
    for ( QHash::iterator it_symbolTable = begin ( ) ;
          it_symbolTable != end ( ) ;
          it_symbolTable ++ )
    {   
        qDebug () << QString("Symbol :%1  |  Location :%2  |")
                     .arg( it_symbolTable.key() , 8 )
                     .arg( it_symbolTable.value() , 6 ) ;
        qDebug () << "------------------------------------------" ;
    }
}
