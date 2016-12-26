#include "Source/Instruction/instructionformat3.h"

InstructionFormat3::InstructionFormat3( void)
{
    m_operandBit = new QBitArray( 6 ) ;
    m_flagBit = new QBitArray ( 6 ) ;
    m_targetBit = new QBitArray ( 12 ) ;
}
