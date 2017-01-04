#ifndef SICXEGENCODEWITHORIGIN_H
#define SICXEGENCODEWITHORIGIN_H

#include <QHash>
#include <QChar>

#include "Source/PassTwo/passtwo.h"

class SICXEGenCodeWithOrigin : public PassTwo
{
    Q_OBJECT
public:
    explicit SICXEGenCodeWithOrigin(QObject *parent = 0);
    virtual void generateObjectCode ( void ) ;
signals:

public slots:
private:
    int m_base ;
    int m_programCounter ;
};

#endif // SICXEGENCODEWITHORIGIN_H
