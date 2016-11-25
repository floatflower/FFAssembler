#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <QObject>
#include <QString>
#include <QHash>

class SymbolTable : public QObject , public QHash < QString , int >
{
    Q_OBJECT
public:
    explicit SymbolTable(QObject *parent = 0);
    void insertSymbol ( QString symbol , int lineNumber , int location ) ;
    void symbolTableTest ( void ) ;
signals:

public slots:
private :
};

#endif // SYMBOLTABLE_H
