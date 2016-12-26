#ifndef PASSONE_H
#define PASSONE_H

#include <QObject>
#include <QString>
#include <QVector>

#include "Source/Instruction/instructionset.h"
#include "Source/SICXESearch/sicxesearch.h"
#include "Source/Table/tablehandler.h"
#include "Source/Instruction/instruction.h"

/*
 * 第一次Pass的節點。
 * 處理順序如下 ：
 * 1. setInputFileName設定輸入檔名稱
 * 2. preprocessor會將原始碼從檔案中一行一行讀出。
 * 3. 每行讀入之後都會先送入formatLine()將每行文字格式化並忽略掉註解。
 * 4. 每一行格式後都會先放入packageInstruction()將指令打包程基礎物件。
 * 5. 送入instructionHandler()透過查找SICXESearch或透過變數大小計算等方式補齊
 *    部份資料，如：指令大小、變數大小等資料，另外計算每個資料的記憶體位置。
 *    取得記憶體位置之後透過tableHandler建立SymbolTable。
 *    只要發現AssemblerDirective的指令就可以做出相應的動作。
 * 6. 將所有包裝好的完整指令存入instructionSet。
 */

class PassOne : public QObject
{
    Q_OBJECT
public:
    explicit PassOne ( QObject *parent = 0 ) ;
    void setInputFileName ( QString inputFileName ) ;
    void preprocessor ( void ) ;
    void package ( QString lineProcessed , int lineNumber ) ;
    void instructionHandler ( Instruction* instruction , int lineNumber ) ;
    QString formatLine ( QString lineRaw ) ;
    InstructionSet* instructionSet ( void ) ;
    int variableSize ( Instruction * instruction , int lineNumber ) ;
    void setTableHandler ( TableHandler* tableHandler ) ;
    void assemblerDirectiveAction ( Instruction *instruction ) ;
    void setSICXESearch ( SICXESearch *sicxeSearch ) ;
    bool noError ( void ) ;
    Instruction* instructionFactory ( int type ) ;
    Instruction* variableFactory ( ) ;
    Instruction* assemblyDirectiveFactory ( ) ;
signals:
public slots:
private:
    QString m_inputFileName ;
    InstructionSet *m_instructionSet ;
    SICXESearch *m_sicxeSearch ;
    TableHandler *m_tableHandler ;
    int m_locationCounter ;
    bool m_noError ;
};

#endif // PASSONE_H
