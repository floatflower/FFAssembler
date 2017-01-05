#include <QDebug>
#include <QtGlobal>

#include "Source/Exception/syntaxexception.h"

SyntaxException::SyntaxException( QString errorMessage )
{
    m_errorMessage = errorMessage ;
}

SyntaxException* SyntaxException::clone() const
{
    return new SyntaxException(*this) ;
}
void SyntaxException::raise() const
{
    throw *this ;
}

void SyntaxException::what()
{
    qInfo() << m_errorMessage ;
}
