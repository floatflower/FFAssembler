#include <QChar>
#include <QString>
#include <QDebug>
#include <QChar>
#include <QBitArray>
#include <QVector>

#include <algorithm>

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
    if ( decimal >= 0 )
    {
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
    }
    else
    {
        int tmp_posDecimal = decimal * (-1) ;
        QBitArray* tmp_posBinary = decimalToBinary(tmp_posDecimal) ;

        int tmp_posBinarySize = tmp_posBinary->size() ;

        int adjustSize = 12 ;

        QBitArray* tmp_adjustBinary = new QBitArray(adjustSize,0) ;

        int i = tmp_posBinarySize - 1 ;
        int j = adjustSize - 1 ;

        for ( ; i >= 0 ; i-- , j -- )
        {
            (*tmp_adjustBinary)[j] = ( *tmp_posBinary )[i] ;
        }

        tmp_posBinary = tmp_adjustBinary ;

        for( int i = 0 ; i < tmp_posBinary->size() ; i ++ )
        {
            (*tmp_posBinary)[i] = !(*tmp_posBinary)[i];
        }
        for ( int i = tmp_posBinary->size() -1 ; i >=0 ; i -- )
        {
            if ( (*tmp_posBinary)[i] == 0 )
            {
                (*tmp_posBinary)[i] = 1 ;
                break ;
            }
            else
            {
                (*tmp_posBinary)[i] = 0 ;
            }
        }
        temp_heximal = binaryToHeximal(*tmp_posBinary) ;
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

QBitArray* GlobalUtility::decimalToBinary ( int decimal )
{
    QVector<int> tmp_binaryVector ;
    while ( decimal != 0 )
    {
        int remainder = decimal % 2 ;
        tmp_binaryVector.push_back(remainder) ;
        decimal /= 2 ;
    }
    int digitLength = tmp_binaryVector.size() ;
    QBitArray *binary = new QBitArray(digitLength) ;
    int i = 0 ;
    for ( QVector<int>::reverse_iterator rit_binaryVector = tmp_binaryVector.rbegin() ;
          rit_binaryVector != tmp_binaryVector.rend() ;
          rit_binaryVector ++ , i ++ )
    {
       binary->setBit( i , *rit_binaryVector ) ;
    }
    return binary ;
}

QString GlobalUtility::binaryToHeximal ( QBitArray binary )
{
    int tmp_instructionSize = binary.size() ;
    int tmp_instructionSizeHalfByte = tmp_instructionSize / 4 ;
    QString tmp_heximal( tmp_instructionSizeHalfByte ) ;

    for ( int i = 0 ; i < tmp_instructionSizeHalfByte ; i ++ )
    {
        int turn = binary.at( 4 * i ) * 8 +
                   binary.at( 4 * i + 1 ) * 4 +
                   binary.at( 4 * i + 2 ) * 2 +
                   binary.at( 4 * i + 3 ) ;
        switch ( turn )
        {
            case 15 : tmp_heximal[i] = 'F' ; break ;
            case 14 : tmp_heximal[i] = 'E' ; break ;
            case 13 : tmp_heximal[i] = 'D' ; break ;
            case 12 : tmp_heximal[i] = 'C' ; break ;
            case 11 : tmp_heximal[i] = 'B' ; break ;
            case 10 : tmp_heximal[i] = 'A' ; break ;
            default : tmp_heximal[i] = QChar( turn + 48 ) ; break ;
        }
    }

    return tmp_heximal ;

}
