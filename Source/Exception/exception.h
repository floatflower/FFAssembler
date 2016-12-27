#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QObject>

class Exception : public QObject
{
    Q_OBJECT
public:
    explicit Exception(QObject *parent = 0);

signals:

public slots:
};

#endif // EXCEPTION_H
