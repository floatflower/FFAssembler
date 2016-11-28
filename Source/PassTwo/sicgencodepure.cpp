#include <QString>

#include "Source/PassTwo/sicgencodepure.h"
#include "Source/globalutility.h"

SICGenCodePure::SICGenCodePure()
{

}

void SICGenCodePure::generateObjectCode ( void )
{
    int lineSize = 0 ;
    int lineStartLocation = 0 ;
    bool lineStart = false ;
    bool forceBreak = false ;
    QString temp_objectCode ;
    QString temp_lineBuffer("") ;
    for ( InstructionSet::iterator it_instructionSet = m_instructionSet->begin ( ) ;
          it_instructionSet < m_instructionSet->end ( ) ;
          it_instructionSet ++ )
    {
        QString temp_operand = ( *it_instructionSet ) -> operand() ;
        if ( m_sicxeSearch -> isOperand ( temp_operand ) )
        {
            QBitArray temp_opcodeHex = m_sicxeSearch -> searchOpcode ( temp_operand ) ;
            QString temp_opcodeStr = GlobalUtility::opcodeToHeximal ( temp_opcodeHex ) ;
            int temp_target ;
            QString temp_targetStr ;
            if ( ( *it_instructionSet ) -> leftTarget() != QString("") )
            {
                temp_target = m_tableHandler ->
                                  symbolTable () ->
                                  value ( ( *it_instructionSet ) -> leftTarget ( ) ) ;
                if ( ( *it_instructionSet ) -> rightTarget() == QString("X") )
                {
                    temp_target += 32768 ;
                }
                temp_targetStr = GlobalUtility::decimalToHeximal ( temp_target ) ;
            }
            else
            {
                temp_targetStr = QString("0000") ;
            }

            if ( ! lineStart )
            {
                lineStartLocation = ( *it_instructionSet ) -> location() ;
                lineStart = true ;
            }

            temp_objectCode = temp_opcodeStr + temp_targetStr ;
        }
        else if ( m_sicxeSearch -> isVariable ( temp_operand ) )
        {
            if ( temp_operand == "RESW" ) {
                temp_objectCode.clear() ;
                forceBreak = true ;
            }
            else if ( temp_operand == "RESB" ) {
                temp_objectCode.clear() ;
                forceBreak = true ;
            }
            else if ( temp_operand == "BYTE" )
            {
                temp_objectCode = parseString ( ( *it_instructionSet ) -> target() ) ;
                // objectCode = QString("%1").arg(objectCode,6,QChar('0')) ;
            }
            else if ( temp_operand == "WORD" )
            {
                bool ok ;
                temp_objectCode = GlobalUtility::decimalToHeximal( ( ( *it_instructionSet ) -> target ( ) ).toInt( &ok , 10 ) ) ;
                temp_objectCode = QString("%1").arg(temp_objectCode,6,QChar('0')) ;
            }
        }
        else if ( m_sicxeSearch -> isReserveWord ( temp_operand ) )
        {
            AssemblerDirectiveAction ( *it_instructionSet ) ;
        }
        if ( ( lineSize + ( *it_instructionSet ) -> size() ) > 30 )
        {
            QString temp_lineStartLocationStr = GlobalUtility::decimalToHeximal(lineStartLocation) ;
            temp_lineBuffer.append("\n") ;
            temp_lineBuffer.prepend ( GlobalUtility::decimalToHeximal( lineSize ) ) ;
            temp_lineBuffer.prepend ( QString("%1").arg(temp_lineStartLocationStr,6,'0') ) ;
            temp_lineBuffer.prepend ("T") ;

            m_compileResult.append( temp_lineBuffer ) ;
            // ---- After output to compileResult ----
            lineSize = 0 ;
            temp_lineBuffer.clear() ;
            lineStartLocation = ( *it_instructionSet )-> location() ;
            forceBreak = false ;
        }
        if ( forceBreak )
        {
            lineSize = 0 ;
            temp_lineBuffer.clear() ;
            forceBreak = false ;
        }
        temp_lineBuffer.append(temp_objectCode) ;
        lineSize += ( *it_instructionSet ) -> size() ;
        temp_objectCode.clear() ;
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
