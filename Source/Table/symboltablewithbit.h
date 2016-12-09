#ifndef SYMBOLTABLEWITHBIT_H
#define SYMBOLTABLEWITHBIT_H

#include <QObject>
#include <QHash>
#include <QBitArray>

class SymbolTableWithBit : public QObject , public QHash < QString , QBitArray >
{
    Q_OBJECT
public:
    explicit SymbolTableWithBit(QObject *parent = 0);
    void insertSymbol ( QString symbol , int lineNumber , int location ) ;
signals:

public slots:
};

#endif // SYMBOLTABLEWITHBIT_H
