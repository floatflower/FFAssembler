#ifndef FFASSEMBLER_H
#define FFASSEMBLER_H

#include <QObject>

#include "commandhandler.h"
#include "passone.h"

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
};

#endif // FFASSEMBLER_H
