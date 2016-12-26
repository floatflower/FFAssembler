#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QObject>
#include <QString>
#include <QBitArray>

/*
 * 用來儲存每個指令的物件
 */

class Instruction : public QObject
{
    Q_OBJECT
public:
    Instruction(QObject *parent = 0);
    QString symbol ( void ) ;
    QString operand ( void ) ;
    QBitArray* operandBit ( void ) ;
    QString target ( void ) ;
    QBitArray* targetBit ( void ) ;
    QBitArray* flagBit ( void ) ;
    QString leftTarget ( void ) ;
    QString rightTarget ( void ) ;
    int size ( void ) ;
    int location ( void ) ;
    int lineNumber ( void ) ;
    void setSymbol ( QString symbol ) ;
    virtual void setOperand ( QString operand ) ;
    virtual void setOperand ( QBitArray* operand ) ;
    virtual void setTarget ( QString target ) ;
    virtual void setTarget ( QBitArray* target ) ;
    void setFlag( QBitArray* flag ) ;
    void setSingleFlag ( int positition , bool bit ) ;
    void setSize ( int size ) ;
    void setLocation ( int location ) ;
    void setLineNumber ( int lineNumber ) ;
signals:

public slots:

protected:
    QString m_symbol ; // 每個指令中的Symbol
    QString m_operand ; // 指令的動作，如果是變數就是變數的型態，也有可能是Assembler directive的指令。
    QString m_target ; // 指令的操作對象。
    QString m_leftTarget ; // 如果字串中有兩個變數以逗點隔開，此為逗點左邊的值。
    QString m_rightTarget ; // 如果字串中有兩個變數以逗點隔開，此為逗點左邊的值。
    int m_size ; // 這個指令的大小
    int m_location ; // 這個指令在記憶體中所佔的位置
    int m_lineNumber ; // 這個指令在原始碼中所在的行數
    QBitArray *m_operandBit ;
    QBitArray *m_flagBit ;
    QBitArray *m_targetBit ;
};

#endif // INSTRUCTION_H
