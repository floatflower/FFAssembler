#include "sicxegencodewithorigin.h"

SICXEGenCodeWithOrigin::SICXEGenCodeWithOrigin(QObject *parent)
{

}
void SICXEGenCodeWithOrigin::generateObjectCode ( void ){
    for ( InstructionSet::iterator it_instructionSet = m_instructionSet->begin() ;
          it_instructionSet != m_instructionSet->end() ;
          it_instructionSet ++ )
    {
    }
}


