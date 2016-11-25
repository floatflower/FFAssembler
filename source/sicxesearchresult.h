#ifndef SICXESEARCHRESULT_H
#define SICXESEARCHRESULT_H

#include <QObject>
#include <QBitArray>

class SICXESearchResult : public QObject
{
    Q_OBJECT
public:
    explicit SICXESearchResult(QObject *parent = 0);
    void setType ( int type ) ;
    void setOpcode ( QBitArray opcode ) ;
    void setSize ( int size ) ;
    int type ( void ) ;
    QBitArray opcode ( void ) ;
    int size ( void ) ;
signals:

public slots:
private :
    int m_type ;
    QBitArray m_opcode ;
    int m_size ;
};

#endif // SICXESEARCHRESULT_H
