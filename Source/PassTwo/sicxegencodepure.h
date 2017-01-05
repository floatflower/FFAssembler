#ifndef SICXEGENCODEPURE_H
#define SICXEGENCODEPURE_H

#include <QHash>
#include <QChar>

#include "Source/PassTwo/passtwo.h"
#include "Source/Instruction/instruction.h"

class SICXEGenCodePure : public PassTwo
{
public:
    SICXEGenCodePure();
    virtual void generateObjectCode ( void ) ;
    void assemblerDirectiveAction ( Instruction* instruction ) ;
    bool immediateAddressingCheck ( QString target ) ;
    bool indirectAddressingCheck ( QString target ) ;
    QString format1Handler ( Instruction* instruction ) ;
    QString format2Handler ( Instruction* instruction ) ;
    QString format3Handler ( Instruction* instruction ) ;
    QString format4Handler ( Instruction* instruction ) ;
    void generateModificationRecord ( void ) ;
private:
    int m_base ;
    int m_programCounter ;
    int m_programStartLocation ;
    QVector< Instruction* > m_modificationVector ;
    QString m_eachLineStartLocation ;
};

#endif // SICXEGENCODEPURE_H
