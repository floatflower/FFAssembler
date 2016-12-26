#ifndef SICXESEARCH_H
#define SICXESEARCH_H

#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHash>
#include <QString>
#include <QSet>
#include <QBitArray>

#include "Source/SICXESearch/sicxesearchresult.h"
#include "Source/Instruction/instruction.h"

/*
 * 用於查詢SIC/XE相關指令的資料庫。
 * 建立初期會先讀入SICXEData/SICXEDataJsonFile.json
 * 之後將此檔案建立成許多關聯是容器QHash
 */

class SICXESearch : public QObject
{
    Q_OBJECT
public:
    explicit SICXESearch(QObject *parent = 0);
    bool readDatabaseFile ( void ) ;
    bool buildDatabase ( void ) ;
    void sicxeSearchTest ( void ) ;
    bool isOperand ( QString word ) ; // 是否為operand
    bool isVariable ( QString  word ) ; // 是否為變數
    bool isReserveWord ( QString word ) ; // 是否為ReserveWord，這裡的ReserveWord就是AssemblerDirective
    bool isLegal ( QString word ) ; // 確定是否為合法operand，確定是否為operand或變數或AssemblerDirective
    SICXESearchResult* search ( Instruction *instruction ) ; // 回傳SICXESearchResult將查詢結果回傳。
    QBitArray searchOpcode ( QString operand ) ; // 查詢Opcode。
    int operandSize ( QString operand ) ;
    int variableSize ( QString variable ) ;
signals:

public slots:
private:
    QJsonDocument sicxeJsonDocument ;
    QJsonObject mainObject ;
    QHash < QString , QBitArray > *m_opcodeTable ;
    QHash < QString , int > *m_opSizeTable ;
    QHash < QString , int > *m_variableSizeTable ;
    QSet < QString > *m_reserveWordTable ;
};

#endif // SICXESEARCH_H
