#include <QDebug>

#include "Source/commandhandler.h"
#include <QString>
#include <QStringList>


CommandHandler::CommandHandler( QObject *parent ): QObject(parent)
{

}

void CommandHandler::setCommand ( int argc , char **argv )
{
    m_argc = argc ;
    m_argv = argv ;
}

void CommandHandler::parseCommand ( void )
{

    // Parsing Command
    for ( int loopL1 = 0 ;
          loopL1 < m_argc ;
          loopL1 ++ )
    {
        if ( QString ( m_argv[ loopL1 ] ) == "--help" || QString ( m_argv[ loopL1 ] ) == "-h" )
        {
            help( ) ;
            exit ( 0 ) ;
        }
        if ( QString ( m_argv[ loopL1 ] ) == "--input" || QString ( m_argv[ loopL1 ] ) == "-i" )
        {
            m_inputFileName = QString ( m_argv[ loopL1 + 1 ] ) ;

            QStringList pattern = m_inputFileName.split(".",QString::SkipEmptyParts) ;

            if ( pattern.at(pattern.size()-1) == "sic" || pattern.at(pattern.size()-1) == "SIC" )
            {
                m_languageMode = 0 ;
            }
            else if ( pattern.at(pattern.size()-1) == "sicxe" || pattern.at(pattern.size()-1) == "SICXE" )
            {
                m_languageMode = 1 ;
            }

            loopL1 ++ ;
        }
        if ( QString ( m_argv[ loopL1 ] ) == "--output" || QString ( m_argv[ loopL1 ] ) == "-o" )
        {
            m_outputFileName = QString ( m_argv[ loopL1 + 1 ] ) ;
            loopL1 ++ ;
        }
        if ( QString ( m_argv[ loopL1 ] ) == "--mode" || QString ( m_argv[ loopL1 ] ) == "-m" )
        {
            bool ok ;
            m_outputMode = QString ( m_argv[ loopL1 + 1 ] ).toInt( &ok , 10 );
            loopL1 ++ ;
        }
    }

    // 確認或修正指令
    if ( m_inputFileName == QString ( "" ) )
    {
        qWarning () << "No Input File." ;
        exit ( 0 ) ;
    }
    if ( m_outputFileName == QString ( "" ) )
    {
        m_outputFileName = "a.txt" ;
    }
    if ( m_outputMode != 0 && m_outputMode != 1 )
    {
        qWarning () << "Mode number" << m_outputMode <<"is illegal." ;
        exit ( 0 ) ;
    }
}

void CommandHandler::parseCommandTest ( void )
{
    qDebug () << "Input File :" << m_inputFileName
              << "Output File :" << m_outputFileName
              << "Output Mode :" << m_outputMode ;
}

void CommandHandler::help ( void )
{
    qInfo () << "./ff\t--input or -i INPUT_FILE_NAME\n"
             << "\t--output or -o OUTPUT_FILE_NAME\n"
             << "\t--mode or -m OUTPUT_MODE";
}

QString CommandHandler::inputFileName ( void )
{
    return m_inputFileName ;
}

QString CommandHandler::outputFileName ( void )
{
    return m_outputFileName ;
}

int CommandHandler::outputMode ( void )
{
    return m_outputMode ;
}

bool CommandHandler::languageMode ( void )
{
    return m_languageMode ;
}
