#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <QObject>
#include <QString>
#include <QHash>

/*
 * 處理系統指令，可以透過CommandHandler取得必要資訊：
 * 1. 輸入檔名稱
 * 2. 輸出檔名稱 ( 如果沒有就會預設為a.txt )
 * 3. 輸出模式 ( 0是原始碼加上ObjectCode的格式，1是純ObjectCode格式 )
 */
class CommandHandler : public QObject
{
    Q_OBJECT
public:
    CommandHandler( QObject *parent = 0 );
    void setCommand ( int argc , char **argv ) ; // 取得由指令列數入的指令
    void parseCommand ( void ) ; // 解譯指令
    void parseCommandTest ( void ) ; // 解譯指令結果測試
    void help ( void ) ; // 幫助訊息
    QString inputFileName ( void ) ;
    QString outputFileName ( void ) ;
    int outputMode ( void ) ;
    bool languageMode ( void ) ;
signals:

public slots:

private:
    int m_argc ;
    char **m_argv ;
    QString m_inputFileName ;
    QString m_outputFileName ;
    int m_outputMode ;
    bool m_languageMode ;
};

#endif // COMMANDHANDLER_H
