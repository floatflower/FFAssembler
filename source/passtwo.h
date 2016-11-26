#ifndef PASSTWO_H
#define PASSTWO_H

#include <QObject>
#include <QString>

#include "instructionset.h"
#include "tablehandler.h"
#include "sicxesearch.h"

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
    void setSICXESearch ( SICXESearch *sicxeSearch ) ;
    QString parseString ( QString data ) ;
signals:

public slots:
protected :
    InstructionSet *m_instructionSet ;
    TableHandler *m_tableHandler ;
    SICXESearch *m_sicxeSearch ;
    QString m_compileResult ;
    QString m_outputFileName ;
};

#endif // PASSTWO_H
