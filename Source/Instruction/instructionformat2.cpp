#include <QBitArray>

#include "Source/Instruction/instructionformat2.h"

InstructionFormat2::InstructionFormat2( void )
{
    m_operandBit = new QBitArray(8) ;
    m_targetBit = new QBitArray(8) ;
}
