#include <QDebug>

#include "ffassembler.h"
#include "passone.h"
#include "passtwo.h"
#include "commandhandler.h"
#include "tablehandler.h"

FFAssembler::FFAssembler(QObject *parent) : QObject(parent)
{
    m_commandHandler = new CommandHandler ;
    m_passOne = new PassOne ;
    m_passTwo = new PassTwo ;
    m_tableHandler = new TableHandler ;
}

void FFAssembler::run ( void )
{
    m_passOne -> setInputFileName ( m_commandHandler -> inputFileName ( ) ) ;
    m_passOne -> setTableHandler ( m_tableHandler ) ;
    m_passOne -> preprocessor ( ) ;

    m_instructionSet = m_passOne -> instructionSet( ) ;
    // Debugging Area
    // m_tableHandler -> symbolTable() -> symbolTableTest () ;
    // m_instructionSet -> instructionSetTest ( ) ;
    if ( m_passOne -> noError ( ) ) exit ( 0 ) ;

    m_passTwo -> setInstructionSet ( m_instructionSet ) ;
    m_passTwo -> setTableHandler ( m_tableHandler ) ;

}

void FFAssembler::setCommand ( int argc , char **argv )
{
    m_commandHandler->setCommand( argc , argv ) ;
    m_commandHandler -> parseCommand ( ) ;
}
