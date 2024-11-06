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
    
    void saveLog(QString& logInfo);//日志信息写入磁盘
    void writeLog(LogLevel logLevel,const QString& fileName,const QString& funcName,int line,const QString& msg);//拼接得到日志信息并写入磁盘
    
private:
    LogDll();
private:
    //日志类所需的一些成员：
    //日志文件的路径、日志文件名

    //QString logFileName;
    QString logFilePathPrefix;
    
    QDir logDir;//日志文件的目录（文件夹）
    QDate logLatestDate;//用来记录当前最新的一个日志文件对应的时间
    QString logLatestFilePathName;//用来记录，现在应该打开的最新的文件，可能是已存在的，也可能用于新创建文件

    QTextStream outLogStream;//用来写日志的流
    //std::unique_ptr<QFile> logFilePtr;//指向唯一的日志文件对象
};



//struct LogPrivate
//{
//    LogPrivate();
//    ~LogPrivate();
//
//    LogLevel logLevel;
//    QDateTime logTime;
//};