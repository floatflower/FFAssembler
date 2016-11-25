#ifndef FFASSEMBLER_H
#define FFASSEMBLER_H

#include <QObject>

#include "commandhandler.h"
#include "passone.h"
#include "instructionset.h"
#include "tablehandler.h"
#include "passtwo.h"

class FFAssembler : public QObject
{
    Q_OBJECT
public:
    explicit FFAssembler(QObject *parent = 0);
    void run ( void ) ;
    void setCommand ( int argc , char **argv ) ;
signals:

public slots:

private:
    CommandHandler *m_commandHandler ;
    PassOne *m_passOne ;
    PassTwo *m_passTwo ;
    InstructionSet *m_instructionSet ;
    TableHandler *m_tableHandler ;
};

#endif // FFASSEMBLER_H
