#ifndef SICXESEARCH_H
#define SICXESEARCH_H

#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHash>
#include <QString>
#include <QSet>

#include "sicxesearchresult.h"
#include "instruction.h"

class SICXESearch : public QObject
{
    Q_OBJECT
public:
    explicit SICXESearch(QObject *parent = 0);
    bool readDatabaseFile ( void ) ;
    bool buildDatabase ( void ) ;
    void sicxeSearchTest ( void ) ;
    bool isOperand ( QString word ) ;
    bool isVariable ( QString  word ) ;
    bool isReserveWord ( QString word ) ;
    bool isLegal ( QString word ) ;
    SICXESearchResult* search ( Instruction *instruction ) ;
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
