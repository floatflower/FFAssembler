#ifndef REGISTERTABLE_H
#define REGISTERTABLE_H

#include <QHash>
#include <QString>

class RegisterTable : public QHash < QString , int >
{
public:
    RegisterTable();
};

#endif // REGISTERTABLE_H
