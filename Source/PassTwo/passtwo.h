#ifndef PASSTWO_H
#define PASSTWO_H

#include <QObject>
#include <QString>

#include "Source/Instruction/instructionset.h"
#include "Source/Table/tablehandler.h"
#include "Source/SICXESearch/sicxesearch.h"

/*
 * 第二次Pass的處理節點
 * 1. 將InstructionSet傳入PassTwo
 * 2. 將TableHandler傳入PassTwo
 * 3. 將SICXESearch傳入PassTwo
 * 4. 設定輸出檔的檔名
 * 5. 透過generateObjectCode()產生將要輸出的資料，並存入m_compileResult。
 * 6. 將m_compileResult透過writeIntoFile()寫入檔案。
 */

class PassTwo : public QObject
{
    Q_OBJECT
public:
    explicit PassTwo(QObject *parent = 0);
    void setInstructionSet ( InstructionSet *instructionSet ) ;
    void setTableHandler ( TableHandler *tableHandler ) ;
    void writeIntoFile ( void ) ;
    void setOutputFileName ( QString outputFileName ) ;
    virtual void generateObjectCode ( void ) ; // 透過繼承PassTwo物件，實做不同的輸出方式。
    void setSICXESearch ( SICXESearch *sicxeSearch ) ;
    QString parseString ( QString data ) ; // 將X'EOF'或C'EOF'解譯為16進位的格式，X直接回傳資料內容，C改成ASCII資料串列。
signals:

public slots:
protected :
    InstructionSet *m_instructionSet ;
    TableHandler *m_tableHandler ;
    SICXESearch *m_sicxeSearch ;
    QString m_compileResult ;
    QString m_outputFileName ;
};

#endif // PASSTWO_H
