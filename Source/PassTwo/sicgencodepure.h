#ifndef SICGENCODEPURE_H
#define SICGENCODEPURE_H

#include "Source/PassTwo/passtwo.h"
#include "Source/Instruction/instruction.h"

class SICGenCodePure : public PassTwo
{
public:
    SICGenCodePure();
    virtual void generateObjectCode ( void ) ;
    void AssemblerDirectiveAction ( Instruction* instruction ) ;
};

#endif // SICGENCODEPURE_H
