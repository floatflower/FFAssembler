#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QIODevice>
#include <QVector>

#include "passone.h"
#include "Source/Instruction/instruction.h"
#include "Source/Instruction/instructionset.h"
#include "Source/SICXESearch/sicxesearch.h"
#include "Source/SICXESearch/sicxesearchresult.h"
#include "Source/globalutility.h"
#include "Source/Table/tablehandler.h"
#include "Source/Instruction/instructionformat1.h"
#include "Source/Instruction/instructionformat2.h"
#include "Source/Instruction/instructionformat3.h"
#include "Source/Instruction/instructionformat4.h"
#include "Source/Instruction/variable.h"
#include "Source/Instruction/assemblydirective.h"

#include "Source/Exception/exception.h"
#include "Source/Exception/syntaxexception.h"

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
    // 確定檔案狀態
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
    // 一行一行的讀取檔案
    QTextStream in ( &inputFile ) ;
    int countLine = 0 ;
    while ( ! in.atEnd( ) )
    {
        countLine ++ ;
        QString readFromFileLineByLine = in.readLine ( ) ;
        QString lineProcessed = formatLine ( readFromFileLineByLine ) ; // 格式化原始碼
        if ( lineProcessed == QString( " " ) )
        {
            continue ;
        }
        try{
            package ( lineProcessed , countLine ) ; // 將格式化的原始碼打包成原始物件
        }catch(SyntaxException& e)
        {
            e.what() ;
            m_noError = false ;
        }
    }

    inputFile.close( ) ;
}

void PassOne::package ( QString lineProcessed , int lineNumber )
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

    // ======= 以上是讀檔和切Token不要動到 ========

    Instruction *tmp_instruction ;

    if ( temp_wordVector.size ( ) == 3 )
    {
        QString tmp_secondKeyword = temp_wordVector.at ( 1 ) ;
        if ( ! m_sicxeSearch -> isLegal ( tmp_secondKeyword ) )
        {
            QString error = QString("At Line %1 : %2 is not a legal operand.")
                            .arg(lineNumber)
                            .arg(tmp_secondKeyword);

            throw SyntaxException( error ) ;
        }

        // ======= Checking Type =======

        if ( m_sicxeSearch -> isOperand ( tmp_secondKeyword ) )
        {
            int format = m_sicxeSearch -> operandSize ( tmp_secondKeyword ) ;
            tmp_instruction = instructionFactory ( format ) ;
        }
        else if ( m_sicxeSearch -> isVariable ( tmp_secondKeyword ) )
        {
            tmp_instruction = variableFactory ( ) ;
        }
        else if ( m_sicxeSearch -> isReserveWord ( tmp_secondKeyword ) )
        {
            tmp_instruction = assemblyDirectiveFactory ( ) ;
        }

        tmp_instruction -> setSymbol ( temp_wordVector.at( 0 ) ) ;
        tmp_instruction -> setOperand ( temp_wordVector.at( 1 ) ) ;
        tmp_instruction -> setTarget ( temp_wordVector.at(2) ) ;
    }
    else if ( temp_wordVector.size ( ) == 2 )
    {
        QString tmp_legalKeyword ;
        int tmp_position ;
        if ( m_sicxeSearch -> isLegal ( temp_wordVector.at( 0 ) ) )
        {
            tmp_legalKeyword = temp_wordVector.at( 0 ) ;
            tmp_position = 0 ;
        }
        else if ( m_sicxeSearch -> isLegal ( temp_wordVector.at ( 1 ) ) )
        {
            tmp_legalKeyword = temp_wordVector.at( 1 ) ;
            tmp_position = 1 ;
        }
        else
        {
            QString error = QString("At Line %1 : %2 or %3 is not a legal operand.")
                    .arg(lineNumber)
                    .arg(temp_wordVector.at(0))
                    .arg(temp_wordVector.at(1));

            throw SyntaxException( error ) ;
        }

        // ======= Check Type =======
        if ( m_sicxeSearch -> isOperand ( tmp_legalKeyword ) )
        {
            int format = m_sicxeSearch -> operandSize ( tmp_legalKeyword ) ;
            tmp_instruction = instructionFactory(format) ;
            tmp_instruction -> setLocation ( m_locationCounter ) ;
            tmp_instruction -> setSize ( format ) ;
        }
        else if ( m_sicxeSearch -> isVariable ( tmp_legalKeyword ) )
        {
            tmp_instruction = variableFactory ( ) ;
        }
        else if ( m_sicxeSearch -> isReserveWord ( tmp_legalKeyword ) )
        {
            tmp_instruction = assemblyDirectiveFactory ( ) ;
        }

        if ( tmp_position == 0 )
        {
            tmp_instruction -> setOperand ( temp_wordVector.at(0) ) ;
            tmp_instruction -> setTarget ( temp_wordVector.at(1) ) ;
        }
        else if ( tmp_position == 1 )
        {
            tmp_instruction -> setSymbol ( temp_wordVector.at(0) ) ;
            tmp_instruction -> setOperand ( temp_wordVector.at(1) ) ;
        }
    }
    else if ( temp_wordVector.size ( ) == 1 )
    {
        if ( ! m_sicxeSearch -> isLegal ( temp_wordVector.at( 0 ) ) )
        {
            QString error = QString("At Line %1 : %2 is not a legal operand.")
                    .arg(lineNumber)
                    .arg(temp_wordVector.at(0));

            throw SyntaxException( error ) ;
        }

        // ======= check type =======

        if ( m_sicxeSearch -> isOperand ( temp_wordVector.at( 0 ) ) )
        {
            int format = m_sicxeSearch -> operandSize ( temp_wordVector.at(0) ) ;
            tmp_instruction = instructionFactory( format ) ;
        }
        else if ( m_sicxeSearch -> isVariable ( temp_wordVector.at( 0 ) ) )
        {
            QString error = QString("At Line %1 : %2 must have a value")
                    .arg(lineNumber)
                    .arg(temp_wordVector.at(0));

            throw SyntaxException( error ) ;
        }
        else if ( m_sicxeSearch -> isReserveWord ( temp_wordVector.at(0) ) )
        {
            tmp_instruction = assemblyDirectiveFactory ( ) ;
        }

        tmp_instruction -> setOperand ( temp_wordVector.at(0) ) ;
    }
    tmp_instruction -> setLineNumber ( lineNumber ) ;
    instructionHandler ( tmp_instruction , lineNumber ) ; // 將打包好的指令送入Handler補齊詳細資訊。
}

void PassOne::instructionHandler ( Instruction* instruction , int lineNumber )
{
    SICXESearchResult *result = m_sicxeSearch -> search ( instruction ) ;

    if ( result -> type () == 3 ) // 此指令type為3，即為Operand
    {
        int size = result -> size ( ) ;
        if ( instruction -> symbol ( ) != QString ("") )
        {
            // 有Symbol時加入將Symbol以及記憶體位置送入symbolTable。
            m_tableHandler -> symbolTable ( ) -> insertSymbol (
                                                                instruction -> symbol( ) ,
                                                                lineNumber ,
                                                                m_locationCounter
                                                               ) ;
        }
        instruction -> setLocation ( m_locationCounter ) ;
        instruction -> setSize ( size ) ;
        m_locationCounter += size ; // locationCounter累加器
    }

    if ( result -> type () == 2 ) // 此指令type為2，即為Variable
    {
        int size = variableSize ( instruction , lineNumber ) ;
        if ( instruction -> symbol ( ) == QString ("") )
        {
            QString error = QString("At Line %1 : %2 must be defined a unique symbol.")
                            .arg(lineNumber)
                            .arg(instruction->operand());
            throw SyntaxException(error) ;
        }
        else if ( instruction -> target() == QString("") )
        {
            QString error = QString("At Line %1 : %2 variable must have a value.")
                            .arg(lineNumber)
                            .arg(instruction->operand());
            throw SyntaxException(error) ;
        }
        else
        {
            // 有Symbol時加入將Symbol以及記憶體位置送入symbolTable。
            m_tableHandler -> symbolTable ( ) -> insertSymbol (
                                                                instruction -> symbol( ) ,
                                                                lineNumber ,
                                                                m_locationCounter
                                                               ) ;
            instruction -> setLocation ( m_locationCounter ) ;
            instruction -> setSize ( size ) ;
            m_locationCounter += size ; // locationCounter累加器
        }
    }
    if ( result -> type () == 1 ) // Assembler Directive
    {
        // 如果是AssemblerDirective的指令，就將instruction送入處理做出相應的動作。
        assemblerDirectiveAction ( instruction ) ;
    }
    m_instructionSet -> insertInstruction ( instruction ) ;
}

QString PassOne::formatLine ( QString lineRaw )
{
    // 將每一行的原始碼格式化為規定格式，並忽略掉註解
    // FFAssembler支援單行註解或行內註解。
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
        if ( size == 0 ) m_noError = false ;
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

Instruction* PassOne::instructionFactory ( int type )
{
    Instruction* tmp_instruction ;
    switch ( type )
    {
        case 1 :
            tmp_instruction = new InstructionFormat1 ;
            break ;
        case 2 :
            tmp_instruction = new InstructionFormat2 ;
            break ;
        case 3 :
            tmp_instruction = new InstructionFormat3 ;
            break ;
        case 4 :
            tmp_instruction = new InstructionFormat4 ;
            break ;
    }

    return tmp_instruction ;
}

Instruction* PassOne::variableFactory ( )
{
    return new Variable ;
}

Instruction* PassOne::assemblyDirectiveFactory (  )
{
    return new AssemblyDirective ;
}
