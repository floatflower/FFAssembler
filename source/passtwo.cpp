#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "passtwo.h"

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

void PassTwo::generateObjectCode ( void )
{

}
