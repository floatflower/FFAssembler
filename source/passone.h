#ifndef PASSONE_H
#define PASSONE_H

#include <QObject>
#include <QString>

class PassOne : public QObject
{
    Q_OBJECT
public:
    explicit PassOne ( QObject *parent = 0 ) ;
    void setInputFileName ( QString inputFileName ) ;
    void preprocessor ( void ) ;
    void packageInstruction ( QString lineProcessed , int lineNumber ) ;
    QString formatLine ( QString lineRaw ) ;
signals:

public slots:
private:
    QString m_inputFileName ;
};

#endif // PASSONE_H
