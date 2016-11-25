#ifndef PASSTWO_H
#define PASSTWO_H

#include <QObject>

#include "instructionset.h"
#include "tablehandler.h"

class PassTwo : public QObject
{
    Q_OBJECT
public:
    explicit PassTwo(QObject *parent = 0);
    void setInstructionSet ( InstructionSet *instructionSet ) ;
    void setTableHandler ( TableHandler *tableHandler ) ;
signals:

public slots:
private :
    InstructionSet *m_instructionSet ;
    TableHandler *m_tableHandler ;
};

#endif // PASSTWO_H
