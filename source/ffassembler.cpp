#include <QDebug>

#include "ffassembler.h"

FFAssembler::FFAssembler(QObject *parent) : QObject(parent)
{
    m_commandHandler = new CommandHandler ;
    m_passOne = new PassOne ;
}

void FFAssembler::run ( void )
{
    m_passOne -> setInputFileName ( m_commandHandler -> inputFileName ( ) ) ;
    m_passOne -> preprocessor ( ) ;

}

void FFAssembler::setCommand ( int argc , char **argv )
{
    m_commandHandler->setCommand( argc , argv ) ;
    m_commandHandler -> parseCommand ( ) ;
}
