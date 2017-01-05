#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <QObject>
#include <QString>
#include <QHash>

/*
 * 繼承QHash物件實現SymbolTable的key=>value對應。
 * 將搜尋的時間複雜度降為O(logn)
 * 透過insertSymbol()來加入而不使用原生的insert()是因為要檢查是否Symbol已經存在，確認不存在才會放入SymbolTable中。
 */

class SymbolTable : public QObject , public QHash < QString , int >
{
    Q_OBJECT
public:
    explicit SymbolTable(QObject *parent = 0);
    void insertSymbol ( QString symbol , int lineNumber , int location ) ;
    QBitArray* bitValue ( QString key ) ;
    void symbolTableTest ( void ) ;
signals:

public slots:
private :
};

#endif // SYMBOLTABLE_H
