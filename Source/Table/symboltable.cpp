#include <QDebug>
#include <QHash>
#include <QString>

#include "Source/Table/symboltable.h"
#include "Source/globalutility.h"

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
        qDebug () << "[Error] At line :"
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

QBitArray* SymbolTable::bitValue ( QString key )
{
    int tmp_value = value( key ) ;

    return GlobalUtility::decimalToBinary( tmp_value ) ;
}
