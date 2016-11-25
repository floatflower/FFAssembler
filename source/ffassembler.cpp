#include <QDebug>

#include "ffassembler.h"
#include "passone.h"
#include "commandhandler.h"
#include "tablehandler.h"

FFAssembler::FFAssembler(QObject *parent) : QObject(parent)
{
    m_commandHandler = new CommandHandler ;
    m_passOne = new PassOne ;
    m_tableHandler = new TableHandler ;
}

void FFAssembler::run ( void )
{
    m_passOne -> setInputFileName ( m_commandHandler -> inputFileName ( ) ) ;
    m_passOne -> setTableHandler ( m_tableHandler ) ;
    m_passOne -> preprocessor ( ) ;

    // m_tableHandler -> symbolTable() -> symbolTableTest () ;
    m_instructionSet = m_passOne -> instructionSet( ) ;
    m_instructionSet -> instructionSetTest ( ) ;
}

void FFAssembler::setCommand ( int argc , char **argv )
{
    m_commandHandler->setCommand( argc , argv ) ;
    m_commandHandler -> parseCommand ( ) ;
}
