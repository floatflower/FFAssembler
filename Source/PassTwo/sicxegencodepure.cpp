#include "Source/PassTwo/sicxegencodepure.h"
#include "Source/globalutility.h"

#include <QBitArray>
#include <QString>
#include <QCharRef>
#include <QDebug>
#include <QVector>

SICXEGenCodePure::SICXEGenCodePure( )
{

}
void SICXEGenCodePure::generateObjectCode ( void ){
    QString eachLine ;
    int index = 0 ;
    int tmp_lineCounter=0 ;
    bool forceBreak = false ;

    for ( InstructionSet::iterator it_instructionSet = m_instructionSet->begin() ;
          it_instructionSet != m_instructionSet->end() ;
          it_instructionSet ++ , index ++ )
    {
        QString tmp_objectCode ;
        QString tmp_operand = ( * it_instructionSet ) -> operand() ;
        int tmp_sizeAdjust = 0 ;
        if ( m_sicxeSearch -> isOperand ( tmp_operand ) )
        {
            int tmp_format = ( *it_instructionSet ) -> size() ;



            m_programCounter += tmp_format ;

            switch ( tmp_format )
            {
                case 1 :
                    tmp_objectCode = format1Handler( *it_instructionSet ) ;
                    tmp_lineCounter += 1 ;
                    tmp_sizeAdjust = 1 ;
                    break ;
                case 2 :
                    tmp_objectCode = format2Handler( *it_instructionSet ) ;
                    tmp_lineCounter += 2 ;
                    tmp_sizeAdjust = 2 ;
                    break ;
                case 3 :
                    tmp_objectCode = format3Handler( *it_instructionSet ) ;

                    tmp_lineCounter += 3 ;
                    tmp_sizeAdjust = 3 ;
                    break ;
                case 4 :
                    tmp_objectCode = format4Handler( *it_instructionSet ) ;
                    tmp_lineCounter += 4 ;
                    tmp_sizeAdjust = 4 ;
                    break ;
            }

        }
        else if ( m_sicxeSearch -> isVariable ( tmp_operand ) )
        {
            int tmp_variableSize = ( *it_instructionSet ) -> size() ;

            m_programCounter += tmp_variableSize ;

            if ( tmp_operand == "RESW" )
            {
                tmp_objectCode.clear() ;
                forceBreak  = true ;
            }
            else if ( tmp_operand == "RESB" )
            {
                tmp_objectCode.clear() ;
                forceBreak = true ;
            }
            else if ( tmp_operand == "BYTE" )
            {
                tmp_objectCode = parseString( ( *it_instructionSet ) -> target() ) ;
                tmp_lineCounter += tmp_variableSize ;
                tmp_sizeAdjust = tmp_variableSize ;
            }
            else if ( tmp_operand == "WORD" )
            {
                bool ok ;
                tmp_objectCode = GlobalUtility::decimalToHeximal( ( ( *it_instructionSet ) -> target() ).toInt(&ok,10) ) ;
                tmp_objectCode = QString("%1").arg(tmp_objectCode,6,QChar('0')) ;
                tmp_lineCounter += tmp_variableSize ;
                tmp_sizeAdjust = tmp_variableSize ;
            }
        }

        // ======== prepend to m_compileResult ========= //

        if ( tmp_lineCounter >= 30 || forceBreak || ( tmp_operand == "END" && tmp_lineCounter!= 0 ) )
        {
            if ( tmp_lineCounter - tmp_sizeAdjust != 0 ){
                eachLine.prepend(GlobalUtility::decimalToHeximal ( tmp_lineCounter - tmp_sizeAdjust )) ;
                eachLine.prepend(m_eachLineStartLocation) ;
                eachLine.prepend("T") ;
                eachLine.append("\n") ;
                m_compileResult += eachLine ;

                // === reinit === //

                tmp_lineCounter = 0 ;

                eachLine.clear() ;
                m_eachLineStartLocation.clear();
                m_eachLineStartLocation = GlobalUtility::decimalToHeximal( ( *it_instructionSet ) -> location() ) ;
                m_eachLineStartLocation = QString("%1").arg(m_eachLineStartLocation,6,'0') ;
                tmp_lineCounter+=tmp_sizeAdjust;
                eachLine.append(tmp_objectCode) ;

            }

            forceBreak = false ;

        }
        else
        {
            eachLine.append(tmp_objectCode) ;
        }

        if ( m_sicxeSearch -> isReserveWord ( tmp_operand ) )
        {
            assemblerDirectiveAction( *it_instructionSet ) ;
        }

    }
}

void SICXEGenCodePure::assemblerDirectiveAction ( Instruction* instruction )
{
    if ( ( instruction -> operand() ) == "START" )
    {
        bool ok ;
        m_eachLineStartLocation = QString("%1").arg(instruction->target(),6,QChar('0'));
        m_programCounter = ( instruction -> target () ).toInt( &ok , 10 ) ;
        m_base = m_programCounter ;
        m_programStartLocation = m_programCounter ;
        QString tmp_programSize = GlobalUtility::decimalToHeximal( m_instructionSet -> totalSize () ) ;
        QString tmp_line = QString("H%1 %2%3\n")
                       .arg(instruction -> symbol())
                       .arg(instruction->target(),6,'0')
                       .arg(tmp_programSize,6,'0') ;
        m_compileResult += tmp_line ;
    }
    if ( ( instruction -> operand () ) == "END" )
    {
        generateModificationRecord();

        int tmp_programBegin = m_programStartLocation ;

        if ( instruction -> target() != QString("") )
        {
            tmp_programBegin = m_tableHandler -> symbolTable() -> value ( instruction -> target() ) ;
        }

        QString tmp_programBeginStr = GlobalUtility::decimalToHeximal( tmp_programBegin ) ;
        tmp_programBeginStr = QString("%1").arg(tmp_programBeginStr,6,QChar('0')) ;

        m_compileResult += ( "M" + tmp_programBeginStr ) ;
    }
    if ( ( instruction -> operand () ) == "BASE" )
    {
        int tmp_baseLocation = m_tableHandler -> symbolTable() -> value ( instruction -> target () ) ;
        m_base = tmp_baseLocation ;
    }
}

bool SICXEGenCodePure::immediateAddressingCheck ( QString target )
{
    return target[0] == QChar('#') ;
}

bool SICXEGenCodePure::indirectAddressingCheck ( QString target )
{
    return target[0] == QChar('@') ;
}

QString SICXEGenCodePure::format1Handler ( Instruction* instruction )
{
    QString tmp_objectCode = instruction->operand () ;
    QBitArray tmp_objectCodeBit = m_sicxeSearch -> searchOpcode ( tmp_objectCode ) ;
    return GlobalUtility::binaryToHeximal( tmp_objectCodeBit ) ;
}
QString SICXEGenCodePure::format2Handler ( Instruction* instruction )
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
QString SICXEGenCodePure::format3Handler ( Instruction* instruction )
{
    QString tmp_operand = instruction -> operand () ;
    QString tmp_target = instruction -> target () ;
    QBitArray tmp_objectCode = m_sicxeSearch -> searchOpcode ( tmp_operand ) ;
    QString tmp_realTarget = tmp_target ;
    QString tmp_realLeftTarget = instruction -> leftTarget () ;

    tmp_objectCode.resize(12);

    if ( immediateAddressingCheck ( tmp_target ) )
    {
        tmp_objectCode.setBit( 7 , 1 ) ; // set i flag
        tmp_realTarget = tmp_target.mid( 1 , tmp_target.size ( ) -1 ) ;
        tmp_realLeftTarget = tmp_realLeftTarget.mid(1,tmp_realLeftTarget.size()-1) ;
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
        tmp_realLeftTarget = tmp_realLeftTarget.mid(1,tmp_realLeftTarget.size()-1) ;
    }
    else{
        tmp_objectCode.setBit(6,1) ;
        tmp_objectCode.setBit(7,1) ;
        if ( instruction -> rightTarget () != QString("") )
        {
            tmp_objectCode.setBit( 8 , 1 ) ;
        }
    }

    QString tmp_objectCodeStr = GlobalUtility::binaryToHeximal( tmp_objectCode ) ;


    if ( tmp_realTarget == QString("") )
    {
        return tmp_objectCodeStr + QString ( "000" ) ;
    }


    int tmp_targetLocation = m_tableHandler -> symbolTable() -> value ( tmp_realTarget ) ;
    int tmp_bTargetLocation = m_tableHandler -> symbolTable() -> value ( tmp_realLeftTarget ) ;

    int distance = tmp_targetLocation - m_programCounter ;
    int baseDistance = tmp_bTargetLocation - m_base ;

    QString tmp_targetStr ;

    // qDebug() << distance << "/" << baseDistance << tmp_operand ;

    if ( distance >= -2048 && distance <= 2047 )
    {
        tmp_objectCode.setBit( 10 , 1 ) ; // set p flag
        tmp_targetStr = GlobalUtility::decimalToHeximal( distance ) ;
    }
    else if ( baseDistance >= 0 && baseDistance <= 4095 )
    {
        tmp_objectCode.setBit( 9 , 1 ) ; // set b flag
        tmp_targetStr = GlobalUtility::decimalToHeximal( baseDistance ) ;
    }
    else{
        qDebug().noquote() << "At Line : "
                 << instruction -> lineNumber()
                 << " : This instruction \""
                 << tmp_operand
                 << "\" doesn't support distance over 4095, maybe use \"+"
                 << tmp_operand
                 << "\" to fix this problem." ;
                 // << tmp_targetLocation << "/" << m_base << "/" << distance << "/" << baseDistance ;
    }

    QString tmp_targetAdjust = QString("%1").arg(tmp_targetStr,3,QChar('0')) ;

    tmp_objectCodeStr = GlobalUtility::binaryToHeximal( tmp_objectCode ) ;

    return tmp_objectCodeStr + tmp_targetAdjust ;

}
QString SICXEGenCodePure::format4Handler ( Instruction* instruction )
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
        m_modificationVector.push_back( instruction ) ;
    }
    else{
        tmp_objectCode.setBit(6,1) ;
        tmp_objectCode.setBit(7,1) ;
        m_modificationVector.push_back( instruction ) ;
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

void SICXEGenCodePure::generateModificationRecord ( void )
{
    for ( QVector<Instruction*>::iterator it_modificationVector = m_modificationVector.begin() ;
          it_modificationVector != m_modificationVector.end() ;
          it_modificationVector ++ )
    {
        QString tmp_operand = ( *it_modificationVector )->operand() ;
        QString tmp_location = GlobalUtility::decimalToHeximal((*it_modificationVector)->location()+1) ;
        QString eachLine = QString("E%1%2\n").arg(tmp_location,5,QChar('0')).arg("05") ;
        m_compileResult += eachLine ;
    }
}
