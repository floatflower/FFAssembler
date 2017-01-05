#include <QDebug>

#include "Source/ffassembler.h"
#include "Source/PassOne/passone.h"
#include "Source/PassTwo/passtwo.h"
#include "Source/commandhandler.h"
#include "Source/Table/tablehandler.h"
#include "Source/PassTwo/sicgencodewithorigin.h"
#include "Source/PassTwo/sicgencodepure.h"
#include "Source/SICXESearch/sicxesearch.h"
#include "Source/globalutility.h"
#include "Source/PassTwo/sicxegencodewithorigin.h"
#include "Source/PassTwo/sicxegencodepure.h"

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
        // 如果在PassOne中遇到錯誤，會一直等到這裡才停止
        // 這樣可以把所有錯誤一次列出來
        // 而不是遇到錯誤就停止。
        qDebug () << "Compile terminated.";
        exit ( 0 ) ;
    }
    m_passTwo = passTwoFactory() ;
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

PassTwo* FFAssembler::passTwoFactory ( void )
{
    if ( m_commandHandler -> languageMode() )
    {
        // SIC Language
        switch ( m_commandHandler -> outputMode() )
        {
            case 0 : return new SICXEGenCodeWithOrigin ; break ;
            case 1 : return new SICXEGenCodePure ; break ;
        }
    }
    else
    {
        // SICXE Language
        switch ( m_commandHandler -> outputMode () )
        {
            case 0 : return new SICGenCodeWithOrigin ; break ;
            case 1 : return new SICGenCodePure;break ;
        }
    }
}
