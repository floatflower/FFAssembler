#ifndef INSTRUCTIONSET_H
#define INSTRUCTIONSET_H

#include <QVector>

#include "instruction.h"
/*
 * 繼承QVector的物件，依序儲存instruction物件指標。
 * 作為各節點中傳遞的介質。
 */
class InstructionSet : public QObject , public QVector < Instruction * >
{
    Q_OBJECT
public:
    explicit InstructionSet( void ) ;
    void instructionSetTest ( void ) ;
};

#endif // INSTRUCTIONSET_H
