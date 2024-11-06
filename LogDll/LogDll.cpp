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
	if (logFilePathPrefix.isEmpty())
	{
		logFilePathPrefix = logPath;
	}
	logDir.setPath(logFilePathPrefix + "/logs");
	if (!logDir.exists())
	{
		logDir.mkpath(logFilePathPrefix + "/logs");  // �ݹ鴴��Ŀ¼
	}
	outLogStream.setCodec("UTF-8");
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
		1������ǰ��һ��ִ�У������������κ���־�ļ������ߣ�������־�ļ���ǡ�������ڽ������־�ļ�����ֱ�Ӵ򿪸��ļ�д������
		2����������־�ļ������������ڽ��죬��Ӧ���´���һ���Խ�������Ϊ������־�ļ�����д������
		��Ҫ���ļ���ֻ���п������Ѵ��ڵ���־�ļ���
		�����ñ���logLatestFilePathName����¼���µ��ļ�����ʲô��ʼ�������µ��ļ����򿪣��������ļ�����
	*/
	if (!logLatestDate.isValid() || logLatestDate != QDate::currentDate())
	{
		logLatestDate = QDate::currentDate();
		QString logFileName = logLatestDate.toString("yyyy-MM-dd") + ".txt";
		logLatestFilePathName = logDir.absoluteFilePath(logFileName);
	}

	//����������־�ļ�
	QFile logFile(logLatestFilePathName);
	if (logFile.open(QIODevice::OpenModeFlag::Append))
	{
		outLogStream.setDevice(&logFile);
		outLogStream << logInfo;
		outLogStream.flush();//����д��
		logFile.close();
	}
	else
	{
		qDebug() << u8"��־�ļ���ʧ��";
	}
}
