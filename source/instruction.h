#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QObject>
#include <QString>

class Instruction : public QObject
{
    Q_OBJECT
public:
    explicit Instruction(QObject *parent = 0);
    QString symbol ( void ) ;
    QString operand ( void ) ;
    QString target ( void ) ;
    int size ( void ) ;
    int location ( void ) ;
    int lineNumber ( void ) ;
    void setSymbol ( QString symbol ) ;
    void setOperand ( QString operand ) ;
    void setTarget ( QString target ) ;
    void setSize ( int size ) ;
    void setLocation ( int location ) ;
    void setLineNumber ( int lineNumber ) ;
signals:

public slots:

private:
    QString m_symbol ;
    QString m_operand ;
    QString m_target ;
    int m_size ;
    int m_location ;
    int m_lineNumber ;
};

#endif // INSTRUCTION_H
