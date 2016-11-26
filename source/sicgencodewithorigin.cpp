#include <QDebug>
#include <QString>
#include <QBitArray>

#include "sicgencodewithorigin.h"
#include "instructionset.h"
#include "instruction.h"
#include "globalutility.h"

SICGenCodeWithOrigin::SICGenCodeWithOrigin()
{

}

void SICGenCodeWithOrigin::generateObjectCode ( void )
{
    for ( InstructionSet::iterator it_instructionSet = m_instructionSet -> begin ( ) ;
          it_instructionSet < m_instructionSet -> end ( ) ;
          it_instructionSet ++ )
    {
        QString objectCode ("");
        QString temp_operand = ( *it_instructionSet ) -> operand() ;
        if ( m_sicxeSearch -> isOperand ( temp_operand ) )
        {
            QBitArray temp_opcodeHex = m_sicxeSearch -> searchOpcode ( temp_operand ) ;
            QString temp_opcodeStr = GlobalUtility::opcodeToHeximal ( temp_opcodeHex ) ;
            int temp_target ;
            QString temp_targetStr ;
            if ( ( *it_instructionSet ) -> target() != QString("") )
            {
                temp_target = m_tableHandler ->
                                  symbolTable () ->
                                  value ( ( *it_instructionSet ) -> target ( ) ) ;
                temp_targetStr = GlobalUtility::decimalToHeximal ( temp_target ) ;
            }
            else
            {
                temp_targetStr = QString("0000") ;
            }
            // qDebug()<< temp_operand << temp_opcodeStr << temp_targetStr << ( *it_instructionSet ) -> target () ;
            objectCode = temp_opcodeStr + temp_targetStr ;
        }
        else if ( m_sicxeSearch -> isVariable ( temp_operand ) )
        {
            if ( temp_operand == "RESW" ) objectCode.clear() ;
            else if ( temp_operand == "RESB" ) objectCode.clear() ;
            else if ( temp_operand == "BYTE" )
            {
                objectCode = parseString ( ( *it_instructionSet ) -> target() ) ;
                objectCode = QString("%1").arg(objectCode,6,QChar('0')) ;
            }
            else if ( temp_operand == "WORD" )
            {
                bool ok ;
                objectCode = GlobalUtility::decimalToHeximal( ( ( *it_instructionSet ) -> target ( ) ).toInt( &ok , 10 ) ) ;
                objectCode = QString("%1").arg(objectCode,6,QChar('0')) ;
            }
        }
        else if ( m_sicxeSearch -> isReserveWord ( temp_operand ) )
        {
            continue ;
        }
        QString eachLine = QString("%1   %2   %3   %4   %5  \n")
                .arg ( GlobalUtility::decimalToHeximal ( ( *it_instructionSet ) -> location() ) , 5 )
                .arg ( ( *it_instructionSet ) -> symbol() , 8 )
                .arg ( ( *it_instructionSet ) -> operand() , 7 )
                .arg ( ( *it_instructionSet ) -> target() , 8 )
                .arg ( objectCode , 7 ) ;
        m_compileResult += eachLine ;
    }

}