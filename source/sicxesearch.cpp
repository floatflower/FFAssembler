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

#include "sicxesearch.h"


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

    QJsonArray temp_reserveWordJsonData = mainObject.value("reserveword").toArray();
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
    for ( QHash< QString , QBitArray >::iterator it_opcodeTable = m_opcodeTable -> begin() ;
          it_opcodeTable != m_opcodeTable -> end() ;
          it_opcodeTable ++ )
    {
        qDebug() << *it_opcodeTable ;
    }
    for ( QHash< QString , int >::iterator it_opSizeTable = m_opSizeTable -> begin() ;
          it_opSizeTable != m_opSizeTable -> end() ;
          it_opSizeTable ++ )
    {
        qDebug() << it_opSizeTable.key() << it_opSizeTable.value() ;
    }
}
