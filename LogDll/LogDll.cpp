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
	if (logFilePathPrefix.isEmpty())
	{
		logFilePathPrefix = logPath;
	}
	logDir.setPath(logFilePathPrefix + "/logs");
	if (!logDir.exists())
	{
		logDir.mkpath(logFilePathPrefix + "/logs");  // 递归创建目录
	}
	outLogStream.setCodec("UTF-8");
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
	logInfo.append(msg).append("\n");

	saveLog(logInfo);
}

void LogDll::saveLog(QString& logInfo)
{
	if (logFilePathPrefix.isEmpty())
	{
		return;
	}

	/*
		1、若当前第一次执行，即还不存在任何日志文件，或者，存在日志文件且恰好是属于今天的日志文件，则直接打开该文件写入数据
		2、若存在日志文件，但并不属于今天，则应该新创建一个以今天日期为名的日志文件，再写入数据
		都要打开文件，只是有可能是已存在的日志文件，
		所以用变量logLatestFilePathName来记录最新的文件名是什么，始终以最新的文件名打开（创建）文件即可
	*/
	if (!logLatestDate.isValid() || logLatestDate != QDate::currentDate())
	{
		logLatestDate = QDate::currentDate();
		QString logFileName = logLatestDate.toString("yyyy-MM-dd") + ".txt";
		logLatestFilePathName = logDir.absoluteFilePath(logFileName);
	}

	//创建并打开日志文件
	QFile logFile(logLatestFilePathName);
	if (logFile.open(QIODevice::OpenModeFlag::Append))
	{
		outLogStream.setDevice(&logFile);
		outLogStream << logInfo;
		outLogStream.flush();//立即写入
		logFile.close();
	}
	else
	{
		qDebug() << u8"日志文件打开失败";
	}
}
