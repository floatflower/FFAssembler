#ifndef SICGENCODEWITHORIGIN_H
#define SICGENCODEWITHORIGIN_H

#include <QString>

#include "passtwo.h"

class SICGenCodeWithOrigin : public PassTwo
{
    Q_OBJECT
public:
    SICGenCodeWithOrigin();
    virtual void generateObjectCode ( void ) ;
};

#endif // SICGENCODEWITHORIGIN_H
