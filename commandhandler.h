#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <QObject>
#include <QString>

class CommandHandler : public QObject
{
    Q_OBJECT
public:
    CommandHandler( QObject *parent = 0 );
    void setCommand ( int argc , char **argv ) ; // 取得由指令列數入的指令
    void parseCommand ( void ) ; // 解譯指令
    void parseCommandTest ( void ) ; // 解譯指令結果測試
    void help ( void ) ; // 幫助訊息
signals:

public slots:

private:
    int m_argc ;
    char **m_argv ;
    QString m_inputFileName ;
    QString m_outputFileName ;
    int m_outputMode ;
};

#endif // COMMANDHANDLER_H
