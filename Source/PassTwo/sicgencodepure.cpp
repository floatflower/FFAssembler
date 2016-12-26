#include <QString>
#include <QChar>
#include <QDebug>

#include "Source/PassTwo/sicgencodepure.h"
#include "Source/globalutility.h"
#include "Source/Instruction/instructionset.h"

SICGenCodePure::SICGenCodePure()
{

}

void SICGenCodePure::generateObjectCode ( void )
{
    int tmp_startLocation ;
    int tmp_lineSize = 0 ;
    bool tmp_lineStart = false ;
    QString tmp_buffer ;
    bool forceBreak = false ;
    for ( InstructionSet::iterator it_instructionSet = m_instructionSet -> begin() ;
          it_instructionSet != m_instructionSet -> end () ;
          it_instructionSet ++ )
    {
        QString tmp_operand = ( *it_instructionSet ) -> operand () ;
        if ( ( tmp_lineSize + ( *it_instructionSet ) -> size () > 30 ) || forceBreak || ( tmp_operand == "END" && tmp_lineSize != 0))
        {
            if ( tmp_lineSize != 0 )
            {
                QString tmp_startLocationStr = GlobalUtility::decimalToHeximal( tmp_startLocation ) ;
                tmp_startLocationStr = QString("%1").arg(tmp_startLocationStr,6,QChar('0')) ;

                QString tmp_lineSizeStr = GlobalUtility::decimalToHeximal( tmp_lineSize ) ;

                tmp_lineSizeStr = QString("%1").arg(tmp_lineSizeStr,2,QChar('0')) ;

                QString tmp_lineResult = tmp_startLocationStr + tmp_lineSizeStr + tmp_buffer ;

                m_compileResult.append("T") ;

                m_compileResult.append( tmp_lineResult ) ;

                m_compileResult.append('\n') ;
            }
            // ----- Reinitialize

            tmp_lineSize = 0 ;
            tmp_lineStart = false ;
            tmp_buffer.clear() ;
            forceBreak = false ;
        }
        QString tmp_objectCode ;
        if ( m_sicxeSearch -> isReserveWord ( tmp_operand ) )
        {
            AssemblerDirectiveAction( *it_instructionSet );
        }
        if ( m_sicxeSearch -> isOperand( tmp_operand ) )
        {

            if ( ! tmp_lineStart )
            {
                tmp_lineStart = true ;
                tmp_startLocation = ( *it_instructionSet ) -> location () ;
            }
            tmp_lineSize += ( *it_instructionSet ) -> size() ;
            QBitArray tmp_opcode = m_sicxeSearch -> searchOpcode( tmp_operand ) ;
            QString tmp_opcodeHex = GlobalUtility::opcodeToHeximal( tmp_opcode ) ;
            int tmp_target ;
            QString tmp_targetStr ;
            if ( ( *it_instructionSet ) -> leftTarget () != QString("") )
            {
                tmp_target = m_tableHandler ->
                             symbolTable() ->
                             value( ( *it_instructionSet ) -> leftTarget( ) ) ;
                if ( ( *it_instructionSet ) -> rightTarget() == QString("X") )
                {
                    tmp_target += 32768 ;
                }
                tmp_targetStr = GlobalUtility::decimalToHeximal(tmp_target) ;
            }
            else{
                tmp_targetStr = QString("0000") ;
            }
            tmp_objectCode = tmp_opcodeHex + tmp_targetStr ;
            tmp_buffer.append( tmp_objectCode ) ;
        }
        if ( m_sicxeSearch -> isVariable( tmp_operand ) )
        {
            if ( tmp_operand == "WORD" )
            {
                bool ok ;
                tmp_objectCode = GlobalUtility::decimalToHeximal( ( ( *it_instructionSet ) -> target ( ) ).toInt( &ok , 10 ) ) ;
                tmp_objectCode = QString("%1").arg(tmp_objectCode,6,QChar('0')) ;
                tmp_lineSize += ( *it_instructionSet ) -> size() ;
                tmp_buffer.append( tmp_objectCode ) ;
            }
            else if ( tmp_operand == "BYTE" )
            {
                tmp_objectCode = parseString ( ( *it_instructionSet ) -> target() ) ;
                tmp_lineSize += ( *it_instructionSet ) -> size() ;
                tmp_buffer.append( tmp_objectCode ) ;
            }
            else if ( tmp_operand == "RESW" )
            {
                forceBreak = true ;
            }
            else if ( tmp_operand == "REWB" )
            {
                forceBreak = true ;
            }
        }
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
