#include "Source/Instruction/instructionformat4.h"

InstructionFormat4::InstructionFormat4( )
{
    m_operandBit = new QBitArray( 6 ) ;
    m_flagBit = new QBitArray( 6 ) ;
    m_targetBit = new QBitArray( 20 ) ;
}
