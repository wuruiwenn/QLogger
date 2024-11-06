#pragma once

#include "logdll_global.h"
#include"qdatetime.h"
#include<qdir.h>
#include<qtextstream.h>

enum class LogLevel
{
    NORMAL = 1,
    WARNING,
    ERROR,
};


class LOGDLL_EXPORT LogDll
{
public:
    static LogDll& GetInstance();
    bool init(QString& logPath);
    
    void saveLog(QString& logInfo);//��־��Ϣд�����
    void writeLog(LogLevel logLevel,const QString& fileName,const QString& funcName,int line,const QString& msg);//ƴ�ӵõ���־��Ϣ��д�����
    
private:
    LogDll();
private:
    //��־�������һЩ��Ա��
    //��־�ļ���·������־�ļ���

    //QString logFileName;
    QString logFilePathPrefix;
    
    QDir logDir;//��־�ļ���Ŀ¼���ļ��У�
    QDate logLatestDate;//������¼��ǰ���µ�һ����־�ļ���Ӧ��ʱ��
    QString logLatestFilePathName;//������¼������Ӧ�ô򿪵����µ��ļ����������Ѵ��ڵģ�Ҳ���������´����ļ�

    QTextStream outLogStream;//����д��־����
    //std::unique_ptr<QFile> logFilePtr;//ָ��Ψһ����־�ļ�����
};



//struct LogPrivate
//{
//    LogPrivate();
//    ~LogPrivate();
//
//    LogLevel logLevel;
//    QDateTime logTime;
//};