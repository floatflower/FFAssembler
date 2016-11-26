#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QIODevice>
#include <QVector>

#include "passone.h"
#include "instruction.h"
#include "instructionset.h"
#include "sicxesearch.h"
#include "sicxesearchresult.h"
#include "globalutility.h"
#include "tablehandler.h"

PassOne::PassOne(QObject *parent) : QObject(parent)
{
    m_instructionSet = new InstructionSet ;
    m_locationCounter = 0 ;
    m_noError = true ;
    // m_sicxeSearch -> sicxeSearchTest ( ) ;
}

void PassOne::setInputFileName ( QString inputFileName )
{
    m_inputFileName = inputFileName ;
}

void PassOne::preprocessor ( void )
{
    QFile inputFile ( m_inputFileName ) ;

    if ( ! inputFile.exists( ) )
    {
        qWarning() << "File:" << m_inputFileName << "is not exist." ;
        exit ( 0 ) ;
    }

    if ( ! inputFile.open ( QIODevice::ReadOnly ) )
    {
        qWarning() << "File:" << m_inputFileName <<"cannot be opened." ;
        exit ( 0 ) ;
    }

    QTextStream in ( &inputFile ) ;
    int countLine = 0 ;
    while ( ! in.atEnd( ) )
    {
        countLine ++ ;
        QString readFromFileLineByLine = in.readLine ( ) ;
        QString lineProcessed = formatLine ( readFromFileLineByLine ) ;
        if ( lineProcessed == QString( " " ) )
        {
            continue ;
        }
        packageInstruction ( lineProcessed , countLine ) ;
    }

    inputFile.close( ) ;
}

void PassOne::packageInstruction ( QString lineProcessed , int lineNumber )
{
    QString temp_word ;
    QVector<QString> temp_wordVector ;
    for ( QString::iterator it_lineProcessed = lineProcessed.begin ( ) ;
          it_lineProcessed < lineProcessed.end ( ) ;
          it_lineProcessed ++ )
    {
        if ( *it_lineProcessed == ' ' )
        {
            temp_wordVector.push_back ( temp_word ) ;
            temp_word.clear() ;
            continue ;
        }
        temp_word.append ( *it_lineProcessed ) ;
    }
    /*for ( QVector<QString>::iterator it_wordVector = temp_wordVector.begin( ) ;
          it_wordVector < temp_wordVector.end( ) ;
          it_wordVector ++ )
    {
        qDebug()<<*it_wordVector ;
    }*/
    Instruction *temp_instruction = new Instruction ;
    if ( temp_wordVector.size ( ) == 3 )
    {
        if ( m_sicxeSearch -> isLegal ( temp_wordVector.at( 1 ) ) )
        {
            temp_instruction -> setSymbol ( temp_wordVector.at ( 0 ) ) ;
            temp_instruction -> setOperand ( temp_wordVector.at ( 1 ) ) ;
            temp_instruction -> setTarget ( temp_wordVector.at ( 2 ) ) ;
        }
        else
        {
            qDebug () << "[Error] At line :"
                      << lineNumber
                      << ":"
                      << temp_wordVector.at ( 1 )
                      << "is not a legal operand." ;
            m_noError = false ;
        }
    }
    else if ( temp_wordVector.size ( ) == 2 )
    {
        if ( m_sicxeSearch -> isLegal ( temp_wordVector.at( 0 ) ) )
        {
            temp_instruction -> setOperand ( temp_wordVector.at ( 0 ) ) ;
            temp_instruction -> setTarget ( temp_wordVector.at ( 1 ) ) ;
        }
        else if ( m_sicxeSearch -> isLegal ( temp_wordVector.at ( 1 ) ) )
        {
            temp_instruction -> setSymbol ( temp_wordVector.at ( 0 ) ) ;
            temp_instruction -> setOperand ( temp_wordVector.at ( 1 ) ) ;
        }
        else
        {
            qDebug () << "[Error] At line :"
                      << lineNumber
                      << ":"
                      << temp_wordVector.at(0)
                      << "or"
                      << temp_wordVector.at(1)
                      << "are neither legal operands." ;
            m_noError = false ;
        }
    }
    else if ( temp_wordVector.size ( ) == 1)
    {
        if ( m_sicxeSearch -> isLegal ( temp_wordVector.at( 0 ) ) )
        {
            temp_instruction -> setOperand ( temp_wordVector.at ( 0 ) ) ;
        }
        else
        {
            qDebug () << "[Error] At line :"
                      << lineNumber
                      << ":"
                      << temp_wordVector.at(0)
                      << "is not a legal operand." ;
            m_noError = false ;
        }
    }

    /*
    qDebug() << temp_instruction->symbol ( )
             << temp_instruction->operand ( )
             << temp_instruction->target ( ) ;
    */
    temp_instruction -> setLineNumber ( lineNumber ) ;
    instructionHandler ( temp_instruction , lineNumber ) ;
}

void PassOne::instructionHandler ( Instruction* instruction , int lineNumber )
{
    SICXESearchResult *result = m_sicxeSearch -> search ( instruction ) ;

    if ( result -> type () == 3 ) // Operand
    {
        int size = result -> size ( ) ;
        if ( instruction -> symbol ( ) != QString ("") )
        {
            m_tableHandler -> symbolTable ( ) -> insertSymbol (
                                                                instruction -> symbol( ) ,
                                                                lineNumber ,
                                                                m_locationCounter
                                                               ) ;
        }
        instruction -> setLocation ( m_locationCounter ) ;
        instruction -> setSize ( size ) ;
        m_locationCounter += size ;
    }

    if ( result -> type () == 2 ) // Variable
    {
        int size = variableSize ( instruction , lineNumber ) ;
        if ( instruction -> symbol ( ) == QString ("") )
        {
            qDebug() << "[Error] At line"
                     << lineNumber
                     << ": Variable :"
                     << instruction -> operand ()
                     << "doesn't have symbol." ;
            m_noError = false ;
            return ;
        }
        else
        {
            m_tableHandler -> symbolTable ( ) -> insertSymbol (
                                                                instruction -> symbol( ) ,
                                                                lineNumber ,
                                                                m_locationCounter
                                                               ) ;
            instruction -> setLocation ( m_locationCounter ) ;
            instruction -> setSize ( size ) ;
            m_locationCounter += size ;
        }
    }
    if ( result -> type () == 1 ) // Assembler Directive
    {
        assemblerDirectiveAction ( instruction ) ;
    }
    m_instructionSet -> push_back ( instruction ) ;
}

QString PassOne::formatLine ( QString lineRaw )
{
    bool wordStart = false ;
    QString temp_lineProcessed ;
    for ( QString::iterator it_lineRaw = lineRaw.begin( ) ;
          it_lineRaw < lineRaw.end( ) ;
          it_lineRaw ++ )
    {
        if ( *it_lineRaw == ' ' || *it_lineRaw == '\t' )
        {
            if ( wordStart )
            {
                temp_lineProcessed.append( ' ' ) ;
            }
            wordStart = false ;
            continue ;
        }
        if ( *it_lineRaw == '.' )
        {
            break ;
        }
        temp_lineProcessed.append ( *it_lineRaw ) ;
        wordStart = true ;
    }
    QString::iterator it_line = temp_lineProcessed.end() - 1  ;
    if ( *it_line != QChar(' ') )
    {
        temp_lineProcessed.append(' ') ;
    }
    return temp_lineProcessed ;
}

InstructionSet* PassOne::instructionSet ( void )
{
    return m_instructionSet ;
}

int PassOne::variableSize ( Instruction * instruction , int lineNumber )
{
    QString variableType = instruction -> operand ( ) ;
    int size = 0 ;
    if ( variableType == "RESW" )
    {
        bool ok ;
        size = ( instruction -> target( ) ).toInt( &ok , 10 ) * 3 ;
    }
    if ( variableType == "RESB" )
    {
        bool ok ;
        size = ( instruction -> target ( ) ).toInt( &ok , 10 ) ;
    }
    if ( variableType == "WORD" )
    {
        size = 3 ;
    }
    if ( variableType == "BYTE" )
    {
        size = GlobalUtility::stringSize( instruction -> target ( ) , lineNumber ) ;
    }
    return size ;
}

void PassOne::setTableHandler ( TableHandler *tableHandler )
{
    m_tableHandler = tableHandler ;
}

void PassOne::assemblerDirectiveAction ( Instruction *instruction )
{
    if ( instruction -> operand ( ) == "START" )
    {
        bool ok ;
        m_locationCounter = ( instruction -> target ( ) ).toInt( &ok , 16 ) ;
    }
}

bool PassOne::noError ( void )
{
    return m_noError ;
}

void PassOne::setSICXESearch ( SICXESearch *sicxeSearch )
{
    m_sicxeSearch = sicxeSearch ;
}
