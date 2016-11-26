#ifndef PASSTWO_H
#define PASSTWO_H

#include <QObject>
#include <QString>

#include "instructionset.h"
#include "tablehandler.h"

class PassTwo : public QObject
{
    Q_OBJECT
public:
    explicit PassTwo(QObject *parent = 0);
    void setInstructionSet ( InstructionSet *instructionSet ) ;
    void setTableHandler ( TableHandler *tableHandler ) ;
    void writeIntoFile ( void ) ;
    void setOutputFileName ( QString outputFileName ) ;
    virtual void generateObjectCode ( void ) ;
signals:

public slots:
protected :
    InstructionSet *m_instructionSet ;
    TableHandler *m_tableHandler ;
    QString m_compileResult ;
    QString m_outputFileName ;
};

#endif // PASSTWO_H
