#include "exception.h"
#include <QDebug>
#include <QtGlobal>

Exception::Exception( )
{

}

void Exception::what( void )
{
    qInfo() << m_errorMessage ;
}
