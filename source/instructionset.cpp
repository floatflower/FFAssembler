#include <QVector>
#include <QDebug>

#include "instructionset.h"

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
        qDebug()<< QString("Symbol : %1  |  Operand : %2  |  Target : %3  |  Size : %4  |  Location : %5  |  LineNumber : %6  |")
                   .arg ( ( *it_test ) -> symbol() , 8  )
                   .arg ( ( *it_test ) -> operand () , 7 )
                   .arg ( ( *it_test ) -> target () , 8 )
                   .arg ( ( *it_test ) -> size () , 6 )
                   .arg ( ( *it_test ) -> location() , 6 )
                   .arg ( ( *it_test ) -> lineNumber() , 5 ) ;
                   ;
        qDebug() << "---------------------------------------------------------------------------------------------------------------------------------" ;
    }
}
