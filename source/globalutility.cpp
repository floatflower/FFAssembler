#include <QChar>
#include <QString>
#include <QDebug>

#include "globalutility.h"

GlobalUtility::GlobalUtility(QObject *parent) : QObject(parent)
{

}
int GlobalUtility::stringSize ( QString dataString , int lineNumber )
{
    if ( ( dataString.at(0) != 'C' ||
           dataString.at(0) != 'X' ) &&
         dataString.at(1) != '\'' &&
         *( dataString.end() -1 ) != '\'' )
    {
        qDebug() << "[Error] At line :"
                 << lineNumber
                 << ":"
                 << "String presentation error.";
        return 0 ;
    }
    int totaldata = 0 ;
    for ( QString::iterator it_dataString = dataString.begin() + 2 ;
          it_dataString < dataString.end() -1 ;
          it_dataString ++ )
    {
        totaldata ++ ;
    }
    return dataString.at(0) == 'C' ? totaldata : totaldata / 2 ;
}
