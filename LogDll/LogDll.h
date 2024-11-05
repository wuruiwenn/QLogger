#pragma once

#include "logdll_global.h"
#include"qdatetime.h"
#include<qdir.h>
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
    
    void saveLog(QString& logInfo);//日志信息写入磁盘
    void writeLog(LogLevel logLevel,const QString& fileName,const QString& funcName,int line,const QString& msg);//拼接得到日志信息并写入磁盘
    
private:
    LogDll();
private:
    //日志类所需的一些成员：
    //日志文件的路径、日志文件名

    QString logFilePath;
    QString logFileName;
    QDir logDir;//日志文件的目录（文件夹）
};



//struct LogPrivate
//{
//    LogPrivate();
//    ~LogPrivate();
//
//    LogLevel logLevel;
//    QDateTime logTime;
//};