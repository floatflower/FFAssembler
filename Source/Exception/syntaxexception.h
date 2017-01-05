#ifndef SYNTAXEXCEPTION_H
#define SYNTAXEXCEPTION_H

#include <QException>

class SyntaxException : public QException
{
public:
    SyntaxException( QString errorMessage );
    virtual SyntaxException* clone() const ;
    virtual void raise() const ;
    void what () ;
private :
    QString m_errorMessage ;
};

#endif // SYNTAXEXCEPTION_H
