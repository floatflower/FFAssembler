#ifndef FFASSEMBLER_H
#define FFASSEMBLER_H

#include <QObject>

#include "commandhandler.h"
#include "Source/PassOne/passone.h"
#include "Source/Instruction/instructionset.h"
#include "Source/Table/tablehandler.h"
#include "Source/PassTwo/passtwo.h"
#include "Source/SICXESearch/sicxesearch.h"

/*
 * 組譯器FFAssembler的主運行程式，程式透過run()函式進行驅動。
 */

class FFAssembler : public QObject
{
    Q_OBJECT
public:
    explicit FFAssembler(QObject *parent = 0);
    void run ( void ) ; // 主程序的驅動。
    void setCommand ( int argc , char **argv ) ; // 從main()中將系統參數放入FFAssembler。
                                                 // 再將收到的指令送到commandHandler，然後解譯指令
    PassTwo* passTwoFactory ( void ) ;
signals:

public slots:

private:
    CommandHandler *m_commandHandler ;
    PassOne *m_passOne ;
    PassTwo *m_passTwo ;
    InstructionSet *m_instructionSet ;
    TableHandler *m_tableHandler ;
    SICXESearch *m_sicxeSearch ;

};

#endif // FFASSEMBLER_H
