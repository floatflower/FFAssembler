#ifndef INSTRUCTIONSET_H
#define INSTRUCTIONSET_H

#include <QVector>

#include "instruction.h"

class InstructionSet : public QObject , public QVector < Instruction * >
{
    Q_OBJECT
public:
    explicit InstructionSet( void ) ;
    void instructionSetTest ( void ) ;
};

#endif // INSTRUCTIONSET_H
