#include "Source/PassTwo/sicxegencodewithorigin.h"
#include "Source/globalutility.h"

#include <QBitArray>
#include <QString>
#include <QCharRef>

SICXEGenCodeWithOrigin::SICXEGenCodeWithOrigin( )
{

}
void SICXEGenCodeWithOrigin::generateObjectCode ( void ){
    for ( InstructionSet::iterator it_instructionSet = m_instructionSet->begin() ;
          it_instructionSet != m_instructionSet->end() ;
          it_instructionSet ++ )
    {
        QString tmp_objectCode ;
        QString tmp_operand = ( * it_instructionSet ) -> operand() ;
        QString eachLine ;
        if ( m_sicxeSearch -> isOperand ( tmp_operand ) )
        {
            int tmp_format = ( *it_instructionSet ) -> size() ;

            m_programCounter += tmp_format ;

            switch ( tmp_format )
            {
                case 1 :
                    tmp_objectCode = format1Handler( *it_instructionSet ) ; break ;
                case 2 :
                    tmp_objectCode = format2Handler( *it_instructionSet ) ; break ;
                case 3 :
                    tmp_objectCode = format3Handler( *it_instructionSet ) ; break ;
                case 4 :
                    tmp_objectCode = format4Handler( *it_instructionSet ) ; break ;
            }
        }
        else if ( m_sicxeSearch -> isVariable ( tmp_operand ) )
        {
            int tmp_variableSize = ( *it_instructionSet ) -> size() ;

            m_programCounter += tmp_variableSize ;

            if ( tmp_operand == "RESW" ) tmp_objectCode.clear() ;
            else if ( tmp_operand == "RESB" ) tmp_objectCode.clear() ;
            else if ( tmp_operand == "BYTE" )
            {
                tmp_objectCode = parseString( ( *it_instructionSet ) -> target() ) ;
            }
            else if ( tmp_operand == "WORD" )
            {
                bool ok ;
                tmp_objectCode = GlobalUtility::decimalToHeximal( ( ( *it_instructionSet ) -> target() ).toInt(&ok,10) ) ;
                tmp_objectCode = QString("%1").arg(tmp_objectCode,6,QChar('0')) ;
            }
        }
        else if ( m_sicxeSearch -> isReserveWord ( tmp_operand ) )
        {
            assemblerDirectiveAction( *it_instructionSet ) ;
        }

        eachLine = QString ("%1%2%3%4%5\n").arg(GlobalUtility::decimalToHeximal(( *it_instructionSet ) -> location() ),4,QChar('0'))
                                           .arg( ( *it_instructionSet ) -> symbol ( ) , 10 )
                                           .arg( ( *it_instructionSet ) -> operand ( ) , 10 )
                                           .arg( ( *it_instructionSet ) -> target( ) , 12 )
                                           .arg( tmp_objectCode , 10 ) ;
        m_compileResult += eachLine ;
    }
}

void SICXEGenCodeWithOrigin::assemblerDirectiveAction ( Instruction* instruction )
{
    if ( ( instruction -> operand() ) == "START" )
    {
        bool ok ;
        m_programCounter = ( instruction -> target () ).toInt( &ok , 10 ) ;
        m_base = m_programCounter ;
    }
}

bool SICXEGenCodeWithOrigin::immediateAddressingCheck ( QString target )
{
    return target[0] == QChar('#') ;
}

bool SICXEGenCodeWithOrigin::indirectAddressingCheck ( QString target )
{
    return target[0] == QChar('@') ;
}

QString SICXEGenCodeWithOrigin::format1Handler ( Instruction* instruction )
{
    QString tmp_objectCode = instruction->operand () ;
    QBitArray tmp_objectCodeBit = m_sicxeSearch -> searchOpcode ( tmp_objectCode ) ;
    return GlobalUtility::binaryToHeximal( tmp_objectCodeBit ) ;
}
QString SICXEGenCodeWithOrigin::format2Handler ( Instruction* instruction )
{
    QString tmp_leftTarget = instruction -> leftTarget() ;
    QString tmp_rightTarget = instruction -> rightTarget () ;

    int tmp_leftRegisterNumber = m_tableHandler -> registerTable() -> value ( tmp_leftTarget ) ;
    int tmp_rightRegisterNumber = m_tableHandler -> registerTable() -> value ( tmp_rightTarget ) ;

    QString tmp_objectCode = instruction -> operand () ;
    QBitArray tmp_objectCodeBit = m_sicxeSearch -> searchOpcode ( tmp_objectCode ) ;

    QString tmp_leftRegisterStr = QString("%1").arg(GlobalUtility::decimalToHeximal(tmp_leftRegisterNumber)) ;

    QString tmp_rightRegisterStr = QString("%1").arg(GlobalUtility::decimalToHeximal(tmp_rightRegisterNumber)) ;

    QString tmp_objectCodeStr = GlobalUtility::binaryToHeximal( tmp_objectCodeBit ) +
                                tmp_leftRegisterStr +
                                tmp_rightRegisterStr ;

    return tmp_objectCodeStr ;


}
QString SICXEGenCodeWithOrigin::format3Handler ( Instruction* instruction )
{
    QString tmp_operand = instruction -> operand () ;
    QString tmp_target = instruction -> target () ;
    QBitArray tmp_objectCode = m_sicxeSearch -> searchOpcode ( tmp_operand ) ;
    QString tmp_realTarget = tmp_target ;

    tmp_objectCode.resize(12);

    if ( immediateAddressingCheck ( tmp_target ) )
    {
        tmp_objectCode.setBit( 7 , 1 ) ; // set i flag
        tmp_realTarget = tmp_target.mid( 1 , tmp_target.size ( ) -1 ) ;
        if ( ! m_tableHandler -> symbolTable() -> contains ( tmp_realTarget ) )
        {
            bool ok ;
            int tmp_immediateValue = tmp_realTarget.toInt(&ok,10);
            QString tmp_immediateValueStr = GlobalUtility::decimalToHeximal(tmp_immediateValue) ;
            QString tmp_objectCodeStr = GlobalUtility::binaryToHeximal( tmp_objectCode ) ;
            tmp_immediateValueStr = QString("%1").arg(tmp_immediateValueStr,3,'0') ;

            return tmp_objectCodeStr + tmp_immediateValueStr ;
        }
    }
    else if ( indirectAddressingCheck ( tmp_target ) )
    {
        tmp_objectCode.setBit(6,1) ; // set n flag
        tmp_realTarget = tmp_target.mid ( 1 , tmp_target.size() - 1 ) ;
    }
    else{
        tmp_objectCode.setBit(6,1) ;
        tmp_objectCode.setBit(7,1) ;
        if ( instruction -> rightTarget () != QString("") )
        {
            tmp_objectCode.setBit( 8 , 1 ) ;
        }
    }

    int tmp_targetLocation = m_tableHandler -> symbolTable() -> value ( tmp_realTarget ) ;

    int distance = tmp_targetLocation - m_programCounter ;

    QString tmp_targetStr ;

    if ( distance >= -2048 && distance <= 2047 )
    {
        tmp_objectCode.setBit( 10 , 1 ) ; // set p flag
        tmp_targetStr = GlobalUtility::decimalToHeximal( distance ) ;
    }
    else if ( distance >= 0 && distance <= 4095 )
    {
        tmp_objectCode.setBit( 9 , 1 ) ; // set b flag
        tmp_targetStr = GlobalUtility::decimalToHeximal( distance ) ;
    }
    else if ( distance < -2048 || distance > 4095 ){
        // error
    }

    QString tmp_targetAdjust = QString("%1").arg(tmp_targetStr,3,QChar('0')) ;

    QString tmp_objectCodeStr = GlobalUtility::binaryToHeximal( tmp_objectCode ) ;

    return tmp_objectCodeStr + tmp_targetAdjust ;

}
QString SICXEGenCodeWithOrigin::format4Handler ( Instruction* instruction )
{
    QString tmp_operand = instruction -> operand () ;
    QString tmp_target = instruction -> target () ;
    QBitArray tmp_objectCode = m_sicxeSearch -> searchOpcode ( tmp_operand ) ;
    QString tmp_realTarget = tmp_target ;

    tmp_objectCode.resize(12);

    tmp_objectCode.setBit(11,1) ;

    if ( immediateAddressingCheck ( tmp_target ) )
    {
        tmp_objectCode.setBit( 7 , 1 ) ; // set i flag
        tmp_realTarget = tmp_target.mid( 1 , tmp_target.size ( ) -1 ) ;
        if ( ! m_tableHandler -> symbolTable() -> contains ( tmp_realTarget ) )
        {
            bool ok ;
            int tmp_immediateValue = tmp_realTarget.toInt(&ok,10);
            QString tmp_immediateValueStr = GlobalUtility::decimalToHeximal(tmp_immediateValue) ;
            QString tmp_objectCodeStr = GlobalUtility::binaryToHeximal( tmp_objectCode ) ;
            tmp_immediateValueStr = QString("%1").arg(tmp_immediateValueStr,5,'0') ;

            return tmp_objectCodeStr + tmp_immediateValueStr ;
        }

    }
    else if ( indirectAddressingCheck ( tmp_target ) )
    {
        tmp_objectCode.setBit(6,1) ; // set n flag
        tmp_realTarget = tmp_target.mid ( 1 , tmp_target.size() - 1 ) ;
    }
    else{
        tmp_objectCode.setBit(6,1) ;
        tmp_objectCode.setBit(7,1) ;
        if ( instruction -> rightTarget () != QString("") )
        {
            tmp_objectCode.setBit( 8 , 1 ) ;
        }
    }

    int tmp_targetLocation = m_tableHandler -> symbolTable() -> value ( tmp_realTarget ) ;

    QString tmp_targetStr = GlobalUtility::decimalToHeximal( tmp_targetLocation ) ;

    QString tmp_targetAdjust = QString("%1").arg(tmp_targetStr,5,QChar('0')) ;

    QString tmp_objectCodeStr = GlobalUtility::binaryToHeximal( tmp_objectCode ) ;

    return tmp_objectCodeStr + tmp_targetAdjust ;
}
