#ifndef TABLEHANDLER_H
#define TABLEHANDLER_H

#include <QObject>

#include "symboltable.h"

/*
 * 所有節點需要存取任何一個Table時都需要透過TableHandler進行存取
 * TableHandler會透過回傳指標將需要的Table回傳給呼叫的節點。
 * 如需要Symbol時呼叫：talbeHandler -> symbolTable() -> FUNCTION()
 */

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
