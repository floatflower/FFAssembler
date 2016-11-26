#include <QDebug>

#include "ffassembler.h"
#include "passone.h"
#include "passtwo.h"
#include "commandhandler.h"
#include "tablehandler.h"
#include "sicgencodewithorigin.h"
#include "sicxesearch.h"
#include "globalutility.h"

FFAssembler::FFAssembler(QObject *parent) : QObject(parent)
{
    m_commandHandler = new CommandHandler ;
    m_passOne = new PassOne ;
    m_passTwo = new PassTwo ;
    m_tableHandler = new TableHandler ;
    m_sicxeSearch = new SICXESearch ;
    m_sicxeSearch -> buildDatabase ( ) ;
}

void FFAssembler::run ( void )
{
    m_passOne -> setInputFileName ( m_commandHandler -> inputFileName ( ) ) ;
    m_passOne -> setTableHandler ( m_tableHandler ) ;
    m_passOne -> setSICXESearch ( m_sicxeSearch ) ;
    m_passOne -> preprocessor ( ) ;

    m_instructionSet = m_passOne -> instructionSet( ) ;
    // Debugging Area
    // m_tableHandler -> symbolTable() -> symbolTableTest () ;
    // m_instructionSet -> instructionSetTest ( ) ;
    if ( ! m_passOne -> noError ( ) )
    {
        qDebug () << "Compile terminated.";
        exit ( 0 ) ;
    }
    m_passTwo = new SICGenCodeWithOrigin ;
    m_passTwo -> setOutputFileName ( m_commandHandler -> outputFileName () ) ;
    m_passTwo -> setInstructionSet ( m_instructionSet ) ;
    m_passTwo -> setTableHandler ( m_tableHandler ) ;
    m_passTwo -> setSICXESearch ( m_sicxeSearch ) ;
    m_passTwo -> generateObjectCode ( ) ;
    m_passTwo -> writeIntoFile ( ) ;

}

void FFAssembler::setCommand ( int argc , char **argv )
{
    m_commandHandler->setCommand( argc , argv ) ;
    m_commandHandler -> parseCommand ( ) ;
}
