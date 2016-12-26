#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QIODevice>
#include <QDebug>
#include <QtGlobal>
#include <QJsonParseError>
#include <QBitArray>
#include <QHash>
#include <QString>
#include <QSet>

#include "Source/SICXESearch/sicxesearch.h"
#include "Source/Instruction/instruction.h"

SICXESearch::SICXESearch(QObject *parent) : QObject(parent)
{
    m_opcodeTable = new QHash < QString , QBitArray > ;
    m_opSizeTable = new QHash < QString , int > ;
    m_variableSizeTable = new QHash < QString , int > ;
    m_reserveWordTable = new QSet < QString > ;
}

bool SICXESearch::readDatabaseFile ( void )
{
    QFile temp_databaseInput ("../../SICXEData/SICXEDataFile.json") ;
    if ( ! temp_databaseInput.exists( ) )
    {
        qWarning() << "Database file not exist." ;
        return false ;
    }

    if ( ! ( temp_databaseInput.open ( QIODevice::ReadOnly ) ) )
    {
        qWarning() << "Database file cannot be read." ;
        return false ;
    }
    QJsonParseError error ;
    sicxeJsonDocument = QJsonDocument::fromJson( temp_databaseInput.readAll() , &error );
    if ( error.error != QJsonParseError::NoError )
    {
        qWarning() << error.errorString().toUtf8();
        return false ;
    }
    mainObject = sicxeJsonDocument.object();
    return true ;
}

bool SICXESearch::buildDatabase ( void )
{
    if ( ! readDatabaseFile ( ) )
    {
        exit ( 0 ) ;
    }

    QJsonArray temp_variableJsonData = mainObject.value("variable").toArray() ;

    for ( QJsonArray::iterator it_variableJsonData = temp_variableJsonData.begin ( ) ;
          it_variableJsonData < temp_variableJsonData.end ( ) ;
          it_variableJsonData ++ )
    {
        QJsonArray temp_eachData = ( *it_variableJsonData ).toArray ( ) ;
        QString temp_variableType = temp_eachData.at( 0 ).toString( ) ;
        int temp_variableSize = temp_eachData.at(1).toInt( ) ;

        m_variableSizeTable -> insert( temp_variableType , temp_variableSize ) ;
    }

    QJsonArray temp_opcodeJsonData = mainObject.value("operand").toArray ( ) ;

    for ( QJsonArray::iterator it_opcodeJsonData = temp_opcodeJsonData.begin ( ) ;
          it_opcodeJsonData < temp_opcodeJsonData.end() ;
          it_opcodeJsonData ++ )
    {
        QJsonArray temp_eachData = ( *it_opcodeJsonData ).toArray ( ) ;
        QString temp_operand = temp_eachData.at(0).toString ( ) ;
        QString temp_opcodeStr = temp_eachData.at(2).toString ( ) ;
        QBitArray temp_opcodeBit(8) ;
        for ( int i = 0 ; i < 8 ; i ++ )
        {
            temp_opcodeBit.setBit( i , temp_opcodeStr[i] == QChar('1') ) ;
        }
        m_opcodeTable -> insert ( temp_operand , temp_opcodeBit ) ;

        int temp_opcodeSize = temp_eachData.at(1).toInt( ) ;
        m_opSizeTable -> insert ( temp_operand , temp_opcodeSize ) ;
    }

    QJsonArray temp_reserveWordJsonData = mainObject.value("assemblerdirective").toArray();
    for ( QJsonArray::iterator it_reserveWordJsonData = temp_reserveWordJsonData.begin();
          it_reserveWordJsonData < temp_reserveWordJsonData.end() ;
          it_reserveWordJsonData ++ )
    {
        m_reserveWordTable -> insert ( ( *it_reserveWordJsonData ).toString( ) ) ;
    }
    return true ;
}

void SICXESearch::sicxeSearchTest ( void )
{
    qDebug() << "Operand versus opcode : " ;
    for ( QHash< QString , QBitArray >::iterator it_opcodeTable = m_opcodeTable -> begin() ;
          it_opcodeTable != m_opcodeTable -> end() ;
          it_opcodeTable ++ )
    {
        qDebug() << "Operand : " << it_opcodeTable.key()
                 << "Opcode : " << it_opcodeTable.value() ;
    }
    qDebug() << "Operand versus size : " ;
    for ( QHash< QString , int >::iterator it_opSizeTable = m_opSizeTable -> begin() ;
          it_opSizeTable != m_opSizeTable -> end() ;
          it_opSizeTable ++ )
    {
        qDebug() << "Operand :" << it_opSizeTable.key()
                 << "Size :" << it_opSizeTable.value() ;
    }
    qDebug() << "Variable versus size : " ;
    for ( QHash< QString , int >::iterator it_variableSizeTable = m_variableSizeTable -> begin() ;
          it_variableSizeTable != m_variableSizeTable -> end() ;
          it_variableSizeTable ++ )
    {
        qDebug() << "Variable :"<< it_variableSizeTable.key()
                 << "Size :"  << it_variableSizeTable.value() ;
    }
    qDebug() << "Assembly directive : " ;
    for ( QSet<QString>::iterator it_reserveWordTable = m_reserveWordTable -> begin () ;
          it_reserveWordTable != m_reserveWordTable -> end() ;
          it_reserveWordTable ++ )
    {
        qDebug() << "Assembly directive :"<< *it_reserveWordTable ;
    }
}
bool SICXESearch::isOperand ( QString word )
{
    return m_opcodeTable -> contains ( word ) ;
}

bool SICXESearch::isVariable ( QString  word )
{
    return m_variableSizeTable -> contains ( word ) ;
}

bool SICXESearch::isReserveWord ( QString word )
{
    return m_reserveWordTable -> contains ( word ) ;
}

bool SICXESearch::isLegal ( QString word )
{
    return word == QString("") ||
           m_opcodeTable -> contains ( word ) ||
           m_variableSizeTable -> contains ( word ) ||
           m_reserveWordTable -> contains ( word ) ;
}

SICXESearchResult* SICXESearch::search ( Instruction *instruction )
{
    SICXESearchResult *result = new SICXESearchResult ;
    QString temp_operand = instruction -> operand ( ) ;
    if ( isOperand ( temp_operand ) )
    {
        result -> setType ( 3 ) ;
        result -> setSize ( m_opSizeTable -> value ( temp_operand ) ) ;
    }
    else if ( isVariable ( temp_operand ) )
    {
        result -> setType ( 2 ) ;
        result -> setSize ( m_variableSizeTable -> value ( temp_operand ) ) ;
    }
    else if ( isReserveWord ( temp_operand ) )
    {
        result -> setType ( 1 ) ;
    }
    return result ;
}

QBitArray SICXESearch::searchOpcode ( QString operand )
{
    return m_opcodeTable -> value ( operand ) ;
}

int SICXESearch::operandSize ( QString operand )
{
    return m_opSizeTable -> value ( operand ) ;
}

int SICXESearch::variableSize ( QString variable )
{
    return m_variableSizeTable -> value ( variable ) ;
}
