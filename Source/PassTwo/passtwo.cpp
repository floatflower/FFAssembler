#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "Source/PassTwo/passtwo.h"
#include "Source/globalutility.h"

PassTwo::PassTwo(QObject *parent) : QObject(parent)
{

}

void PassTwo::setInstructionSet ( InstructionSet *instructionSet )
{
    m_instructionSet = instructionSet ;
}

void PassTwo::setTableHandler ( TableHandler *tableHandler )
{
    m_tableHandler = tableHandler ;
}

void PassTwo::writeIntoFile ( void )
{
    QFile outputFile ( m_outputFileName ) ;
    if ( ! outputFile.open ( QIODevice::WriteOnly | QIODevice::Truncate ) )
    {
        qDebug() << "Target output file cannot be opened." ;
    }
    QTextStream out ( &outputFile ) ;
    out << m_compileResult ;
}

void PassTwo::setOutputFileName ( QString outputFileName )
{
    m_outputFileName = outputFileName ;
}

void PassTwo::setSICXESearch ( SICXESearch *sicxeSearch )
{
    m_sicxeSearch = sicxeSearch ;
}

void PassTwo::generateObjectCode ( void )
{

}

QString PassTwo::parseString ( QString data )
{
    // 將C'STRING'或X'HEX_STRING'解譯為十六位元ASCII或十六位元。
    QString turn("") ;
    if ( data.at ( 0 ) == 'X' )
    {
        int str_length = data.length ( ) ;
        turn = data.mid ( 2 , str_length - 3 ) ;
    }
    if ( data.at ( 0 ) == 'C' )
    {

        for ( QString::iterator it_data = data.begin ( ) + 2 ;
              it_data < data.end ( ) - 1 ;
              it_data ++ )
        {
            int temp_ascii = ( int ) ( *it_data ).toLatin1() ;
            QString asciiNumber = GlobalUtility::decimalToHeximal ( temp_ascii ) ;
            turn += asciiNumber ;
        }   
    }
    return turn ;
}
