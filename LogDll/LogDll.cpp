#include "LogDll.h"
#include<qDebug>
#include<qcoreapplication.h>
#include<qfile.h>
#include<qtextstream.h>


LogDll::LogDll()
{
	//std::cout << "���캯��\n";
	//qDebug() << "���캯��\n";
}

LogDll& LogDll::GetInstance() {
	static LogDll logDll;
	return logDll;
}


bool LogDll::init(QString& logPath) {
	//��ʼ����ʱ�򣺳�ʼ����־�ļ�Ӧ�ô洢��·�����ļ����Ļ�Ӧ���������洢��ʱ�����ɣ���ʱ��������
	if (logFilePath.isEmpty())
	{
		logFilePath = logPath;
	}
	return true;
}

void LogDll::writeLog(LogLevel logLevel, const QString& fileName, const QString& funcName,int line, const QString& msg)
{
	//��־���ͣ����������桢����
	//��־ʱ�䣺
	//ִ���ļ����������ú���������
	//������Ϣ
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

	//����������־�ļ�
	QFile logFile(logFileAbsolutePath);
	if (logFile.open(QIODevice::ReadWrite | QIODevice::Append))
	{
		QTextStream stream(&logFile);
		stream.setCodec("UTF-8");
		stream << logInfo;
		stream.flush();//����д��
		logFile.close();
	}
	else
	{
		qDebug() << u8"��־�ļ���ʧ��";
	}
}
