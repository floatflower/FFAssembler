#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>
#include <QException>

class Exception : public QException
{
public:
    explicit Exception( );
    virtual void what( void ) ;

protected :
    QString m_errorMessage ;
};

#endif // EXCEPTION_H
