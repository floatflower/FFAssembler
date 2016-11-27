#include <QChar>
#include <QString>
#include <QDebug>
#include <QChar>
#include <QBitArray>

#include "Source/globalutility.h"

GlobalUtility::GlobalUtility(QObject *parent) : QObject(parent)
{

}
int GlobalUtility::stringSize ( QString dataString , int lineNumber )
{
    if ( ( dataString.at(0) != 'C' ||
           dataString.at(0) != 'X' ) &&
         dataString.at(1) != '\'' &&
         *( dataString.end() -1 ) != '\'' )
    {
        // 先驗證字串指令格式，如果格式錯誤則會回傳size為0。
        qDebug() << "[Error] At line :"
                 << lineNumber
                 << ":"
                 << "String presentation error.";
        return 0 ;
    }
    int totaldata = dataString.length() - 3 ;
    return dataString.at(0) == 'C' ? totaldata : totaldata / 2 ;
}

QString GlobalUtility::decimalToHeximal ( int decimal )
{
    QString temp_heximal("") ;
    temp_heximal.clear() ;
    while ( true )
    {
        int temp_remainder = decimal % 16 ;
        decimal /= 16 ;
        switch ( temp_remainder )
        {
            case 15 : temp_heximal.prepend('F') ; break ;
            case 14 : temp_heximal.prepend('E') ; break ;
            case 13 : temp_heximal.prepend('D') ; break ;
            case 12 : temp_heximal.prepend('C') ; break ;
            case 11 : temp_heximal.prepend('B') ; break ;
            case 10 : temp_heximal.prepend('A') ; break ;
            default : temp_heximal.prepend( QChar ( temp_remainder + 48 ) ) ;
        }
        if ( decimal == 0 ) break ;
    }
    return temp_heximal ;
}

QString GlobalUtility::opcodeToHeximal ( QBitArray opcode )
{
    QString hex_opcode (2) ;
    for ( int i = 0 ; i < 2 ; i ++ )
    {
        int turn = opcode.at( 4 * i )*8 + opcode.at( 4 * i + 1 )*4 + opcode.at( 4 * i + 2 )*2 + opcode.at( 4 * i + 3)*1 ;
        switch ( turn )
        {
            case 15 : hex_opcode[i] = 'F' ; break ;
            case 14 : hex_opcode[i] = 'E' ; break ;
            case 13 : hex_opcode[i] = 'D' ; break ;
            case 12 : hex_opcode[i] = 'C' ; break ;
            case 11 : hex_opcode[i] = 'B' ; break ;
            case 10 : hex_opcode[i] = 'A' ; break ;
            default : hex_opcode[i] = QChar ( turn + 48 ) ; break ;
        }

    }
    return hex_opcode ;
}
