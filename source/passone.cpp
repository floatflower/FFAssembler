#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QIODevice>
#include <QVector>

#include "passone.h"
#include "instruction.h"

PassOne::PassOne(QObject *parent) : QObject(parent)
{
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
        if ( lineProcessed == QString( "" ) )
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
        temp_instruction -> setSymbol ( temp_wordVector.at ( 0 ) ) ;
        temp_instruction -> setOperand ( temp_wordVector.at ( 1 ) ) ;
        temp_instruction -> setTarget ( temp_wordVector.at ( 2 ) ) ;
    }
    else if ( temp_wordVector.size ( ) == 2 )
    {
        temp_instruction -> setOperand ( temp_wordVector.at ( 0 ) ) ;
        temp_instruction -> setTarget ( temp_wordVector.at ( 1 ) ) ;
    }
    else if ( temp_wordVector.size ( ) == 1)
    {
        temp_instruction -> setOperand ( temp_wordVector.at ( 0 ) ) ;
    }
    /*
    qDebug()<< temp_instruction->symbol ( )
            << temp_instruction->operand ( )
            << temp_instruction->target ( ) ;
    */
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
    return temp_lineProcessed ;
}
