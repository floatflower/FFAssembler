#ifndef PASSONE_H
#define PASSONE_H

#include <QObject>
#include <QString>

#include "instructionset.h"
#include "sicxesearch.h"

class PassOne : public QObject
{
    Q_OBJECT
public:
    explicit PassOne ( QObject *parent = 0 ) ;
    void setInputFileName ( QString inputFileName ) ;
    void preprocessor ( void ) ;
    void packageInstruction ( QString lineProcessed , int lineNumber ) ;
    void instructionHandler ( Instruction* instruction ) ;
    QString formatLine ( QString lineRaw ) ;
    InstructionSet* instructionSet ( void ) ;
signals:

public slots:
private:
    QString m_inputFileName ;
    InstructionSet *m_instructionSet ;
    SICXESearch *m_sicxeSearch ;
};

#endif // PASSONE_H
