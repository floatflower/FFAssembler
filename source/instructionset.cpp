#include <QVector>
#include <QDebug>

#include "instructionset.h"

InstructionSet::InstructionSet( void )
{

}

void InstructionSet::instructionSetTest ( void )
{
    for ( QVector < Instruction * >::iterator it_test = begin( ) ;
          it_test < end ( ) ;
          it_test ++ )
    {
        qDebug()<< "Symbol :" << ( *it_test ) -> symbol ( )
                << "/Operand :" << ( *it_test ) -> operand ( )
                << "/Target :" << ( *it_test ) -> target ( ) ;
    }
}
