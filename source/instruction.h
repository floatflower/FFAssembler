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
    void setSymbol ( QString symbol ) ;
    void setOperand ( QString operand ) ;
    void setTarget ( QString target ) ;
signals:

public slots:

private:
    QString m_symbol ;
    QString m_operand ;
    QString m_target ;
};

#endif // INSTRUCTION_H
