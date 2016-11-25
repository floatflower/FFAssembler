#ifndef PASSONE_H
#define PASSONE_H

#include <QObject>
#include <QString>

#include "instructionset.h"
#include "sicxesearch.h"
#include "tablehandler.h"
#include "instruction.h"

class PassOne : public QObject
{
    Q_OBJECT
public:
    explicit PassOne ( QObject *parent = 0 ) ;
    void setInputFileName ( QString inputFileName ) ;
    void preprocessor ( void ) ;
    void packageInstruction ( QString lineProcessed , int lineNumber ) ;
    void instructionHandler ( Instruction* instruction , int lineNumber ) ;
    QString formatLine ( QString lineRaw ) ;
    InstructionSet* instructionSet ( void ) ;
    int variableSize ( Instruction * instruction , int lineNumber ) ;
    void setTableHandler ( TableHandler* tableHandler ) ;
    void assemblerDirectiveAction ( Instruction *instruction ) ;
signals:

public slots:
private:
    QString m_inputFileName ;
    InstructionSet *m_instructionSet ;
    SICXESearch *m_sicxeSearch ;
    TableHandler *m_tableHandler ;
    int m_locationCounter ;
};

#endif // PASSONE_H
