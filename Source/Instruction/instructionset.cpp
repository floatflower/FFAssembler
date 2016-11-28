#include <QVector>
#include <QDebug>

#include "Source/Instruction/instructionset.h"

InstructionSet::InstructionSet( void )
{

}

void InstructionSet::instructionSetTest ( void )
{
    qDebug () << "Instruction Set : \n" ;
    for ( QVector < Instruction * >::iterator it_test = begin( ) ;
          it_test < end ( ) ;
          it_test ++ )
    {
        qDebug()<< QString("Symbol : %1  |  Operand : %2  |  Target : %3  |  LeftTaget : %4  |  RightTarget : %5  |  Size : %6  |  Location : %7  |  LineNumber : %8  |")
                   .arg ( ( *it_test ) -> symbol() , 8  )
                   .arg ( ( *it_test ) -> operand () , 7 )
                   .arg ( ( *it_test ) -> target () , 8 )
                   .arg ( ( *it_test ) -> leftTarget () , 8 )
                   .arg ( ( *it_test ) -> rightTarget () , 3 )
                   .arg ( ( *it_test ) -> size () , 6 )
                   .arg ( ( *it_test ) -> location() , 6 )
                   .arg ( ( *it_test ) -> lineNumber() , 5 ) ;
                   ;
        qDebug() << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" ;
    }
}

void InstructionSet::insertInstruction ( Instruction* instruction )
{
    m_totalSize += instruction -> size () ;
    push_back ( instruction ) ;
}

int InstructionSet::totalSize ( void )
{
    return m_totalSize ;
}
