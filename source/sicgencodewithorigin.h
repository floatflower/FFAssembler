#ifndef SICGENCODEWITHORIGIN_H
#define SICGENCODEWITHORIGIN_H

#include <QString>

#include "passtwo.h"

class SICGenCodeWithOrigin : public PassTwo
{
    Q_OBJECT
public:
    SICGenCodeWithOrigin();
    virtual void generateObjectCode ( void ) ; // 實做PassTwo物件中的generateObjectCode。
};

#endif // SICGENCODEWITHORIGIN_H
