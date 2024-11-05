#include "LogDll.h"
#include<qDebug>
#include<qcoreapplication.h>
#include<qfile.h>
#include<qtextstream.h>


LogDll::LogDll()
{
	//std::cout << "构造函数\n";
	//qDebug() << "构造函数\n";
}

LogDll& LogDll::GetInstance() {
	static LogDll logDll;
	return logDll;
}


bool LogDll::init(QString& logPath) {
	//初始化的时候：初始化日志文件应该存储的路径，文件名的话应该是真正存储的时候生成（用时间来代表）
	if (logFilePath.isEmpty())
	{
		logFilePath = logPath;
	}
	return true;
}

void LogDll::writeLog(LogLevel logLevel, const QString& fileName, const QString& funcName,int line, const QString& msg)
{
	//日志类型：正常、警告、错误
	//日志时间：
	//执行文件名、所调用函数、行数
	//内容信息
	QString logInfo;
	QString timeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:dd");
	logInfo.append(timeStr).append(" | ");
	switch (logLevel)
	{
	case LogLevel::NORMAL:
		logInfo.append("Normal");
		break;
	case LogLevel::WARNING:
		logInfo.append("Warning");
		break;
	case LogLevel::ERROR:
		logInfo.append("Error");
		break;
	default:
		break;
	}
	logInfo.append(" | ");
	logInfo.append(fileName).append(" | ");
	logInfo.append(funcName).append(" | ");
	logInfo.append(QString::number(line)).append(" | ");
	logInfo.append(msg);

	saveLog(logInfo);
}

void LogDll::saveLog(QString& logInfo)
{
	if (logFilePath.isEmpty())
	{
		return;
	}
	QDir tmpDir(logFilePath);
	if (!tmpDir.exists())
	{
		tmpDir.mkpath(".");
	}
	QString logFileName = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + ".txt";
	QString logFileAbsolutePath = logDir.absoluteFilePath(logFileName);

	//创建并打开日志文件
	QFile logFile(logFileAbsolutePath);
	if (logFile.open(QIODevice::ReadWrite | QIODevice::Append))
	{
		QTextStream stream(&logFile);
		stream.setCodec("UTF-8");
		stream << logInfo;
		stream.flush();//立即写入
		logFile.close();
	}
	else
	{
		qDebug() << u8"日志文件打开失败";
	}
}
