#ifndef GLOBALUTILITY_H
#define GLOBALUTILITY_H

#include <QObject>
#include <QBitArray>

/*
 * 組譯器中常用的工具，如十進位轉十六進位或計算字串大小等。
 */

class GlobalUtility : public QObject
{
    Q_OBJECT
public:
    explicit GlobalUtility(QObject *parent = 0);
    static int stringSize ( QString string , int lineNumber ) ; // 計算字串大小
    static QString decimalToHeximal ( int decimal ) ; // 十進位轉十六進位
    static QString opcodeToHeximal ( QBitArray opcode ) ; // 將Opcode換算為十六進位
    static QBitArray* decimalToBinary ( int decimal ) ; // 十進位轉二進位
    static QString binaryToHeximal ( QBitArray instructionBit ) ;
signals:

public slots:
};

#endif // GLOBALUTILITY_H
