#include <QString>

#include "Source/PassTwo/sicgencodepure.h"
#include "Source/globalutility.h"
#include "Source/Instruction/instructionset.h"

SICGenCodePure::SICGenCodePure()
{

}

void SICGenCodePure::generateObjectCode ( void )
{
    for ( InstructionSet::iterator it_instructionSet = m_instructionSet -> begin() ;
          it_instructionSet != m_instructionSet -> end () ;
          it_instructionSet ++ )
    {

    }
}

void SICGenCodePure::AssemblerDirectiveAction ( Instruction* instruction )
{
    QString temp_operand = instruction -> operand() ;
    QString buffer("") ;
    bool needToAppend = false ;
    if ( temp_operand == "START" )
    {
        buffer.append("H") ;
        buffer.append( instruction -> symbol ( ) ) ;
        buffer.append(" ") ;
        buffer.append( QString("%1").arg( instruction -> target() , 6 , '0' ) ) ;
        QString temp_totalSize = GlobalUtility::decimalToHeximal ( m_instructionSet -> totalSize ( ) ) ;
        buffer.append( QString("%1").arg( temp_totalSize , 6 , '0' ) ) ;
        buffer.append("\n") ;
        needToAppend = true ;
    }
    else if ( temp_operand == "END" )
    {
        if ( instruction -> target() != QString("") )
        {
            int temp_startLocation = m_tableHandler -> symbolTable() -> value( instruction -> target ( ) ) ;
            QString temp_startLocationStr = GlobalUtility::decimalToHeximal ( temp_startLocation ) ;
            buffer.append("E") ;
            buffer.append( QString("%1").arg( temp_startLocationStr , 6 , '0' ) ) ;

        }
        needToAppend = true ;
    }
    if ( needToAppend )
    {
        m_compileResult.append( buffer );
    }
}
