#include <QtCore/QCoreApplication>
#include "LogDll.h"
#include<qdebug.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    QString logPath = QCoreApplication::applicationDirPath();
    qDebug() << "logPath = " << logPath;
    LogDll& log = LogDll::GetInstance();

    log.init(logPath);
    log.writeLog(LogLevel::ERROR,"Main.cpp","main",16,u8"日志信息");

    return a.exec();
}
