#ifndef GLOBALUTILITY_H
#define GLOBALUTILITY_H

#include <QObject>
#include <QBitArray>

class GlobalUtility : public QObject
{
    Q_OBJECT
public:
    explicit GlobalUtility(QObject *parent = 0);
    static int stringSize ( QString string , int lineNumber ) ;
    static QString decimalToHeximal ( int decimal ) ;
    static QString opcodeToHeximal ( QBitArray opcode ) ;
signals:

public slots:
};

#endif // GLOBALUTILITY_H
