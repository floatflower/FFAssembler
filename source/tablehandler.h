#ifndef TABLEHANDLER_H
#define TABLEHANDLER_H

#include <QObject>

#include "symboltable.h"

class TableHandler : public QObject
{
    Q_OBJECT
public:
    explicit TableHandler(QObject *parent = 0);
    SymbolTable* symbolTable( void ) ;
signals:

public slots:
private :
    SymbolTable *m_symbolTable ;
};

#endif // TABLEHANDLER_H
