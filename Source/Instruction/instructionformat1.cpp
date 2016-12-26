#include <QBitArray>

#include "Source/Instruction/instructionformat1.h"

InstructionFormat1::InstructionFormat1( void )
{
    m_operandBit = new QBitArray (8) ;
}
