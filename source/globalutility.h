#ifndef GLOBALUTILITY_H
#define GLOBALUTILITY_H

#include <QObject>

class GlobalUtility : public QObject
{
    Q_OBJECT
public:
    explicit GlobalUtility(QObject *parent = 0);
    static int stringSize ( QString string , int lineNumber ) ;
signals:

public slots:
};

#endif // GLOBALUTILITY_H
