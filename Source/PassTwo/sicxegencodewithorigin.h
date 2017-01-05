#ifndef SICXEGENCODEWITHORIGIN_H
#define SICXEGENCODEWITHORIGIN_H

#include <QHash>
#include <QChar>

#include "Source/PassTwo/passtwo.h"
#include "Source/Instruction/instruction.h"

class SICXEGenCodeWithOrigin : public PassTwo
{
public:
    explicit SICXEGenCodeWithOrigin( );
    virtual void generateObjectCode ( void ) ;
    void assemblerDirectiveAction ( Instruction* instruction ) ;
    bool immediateAddressingCheck ( QString target ) ;
    bool indirectAddressingCheck ( QString target ) ;
    QString format1Handler ( Instruction* instruction ) ;
    QString format2Handler ( Instruction* instruction ) ;
    QString format3Handler ( Instruction* instruction ) ;
    QString format4Handler ( Instruction* instruction ) ;
signals:

public slots:
private:
    int m_base ;
    int m_programCounter ;
};

#endif // SICXEGENCODEWITHORIGIN_H
