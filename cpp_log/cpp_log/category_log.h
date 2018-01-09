#pragma once
#ifndef _CATEGORY_LOG_H_
#define _CATEGORY_LOG_H_


#include <iostream>
#include <string>

// 通用的转为string的函数
template<class T>
inline std::string ToString(const T& a)
{
	return std::to_string(a);
}
template<>
inline std::string ToString(const std::string& a)
{
	return a;
}
inline std::string ToString(const char* a)
{
	return std::string(a);
}

// 日志流
template<int StaticLogLevel>
class LogArchive
{
public:
	LogArchive(int logLevel, const char* classTag, const char* logTag)
		: EnvLogLevel(logLevel), ClassTag(classTag), LogTag(logTag)
	{
		// std::cout << "[" << Tag << "] " << "StringArchive()" << std::endl;
	}
	~LogArchive()
	{
		// 如果日志等级比环境等级高，那么就打印日志。
		if (StaticLogLevel >= EnvLogLevel)
		{
			std::cout << "[" << ClassTag << "][" << LogTag << "]" << str.c_str() << std::endl;
		}
		// std::cout << Tag << "~StringArchive()" << std::endl;
	}
	template<class T2>
	LogArchive & operator << (const T2& a)
	{
		if (StaticLogLevel >= EnvLogLevel)
		{
			str += ToString(a);
		}
		return *this;
	}

	static void Delete(LogArchive* ptr)
	{
		delete ptr;
	}

private:
	std::string str;
	int EnvLogLevel;
	const char* ClassTag;
	const char* LogTag;
};

// 默认日志等级分类
enum ELogLevel
{
	ELogDebug,
	ELogInfo,
	ELogWarning,
	ELogError,
	ELogFatal,
};

// 默认对应的日志输出方式。
class DebugLogArchive : public LogArchive<ELogDebug>
{
public:
	DebugLogArchive(int logLevel, const char* tag) : LogArchive(logLevel, tag, "debug")
	{}
};
class InfoLogArchive : public LogArchive<ELogInfo>
{
public:
	InfoLogArchive(int logLevel, const char* tag) : LogArchive(logLevel, tag, "info")
	{}
};
class WarnLogArchive : public LogArchive<ELogWarning>
{
public:
	WarnLogArchive(int logLevel, const char* tag) : LogArchive(logLevel, tag, "warning")
	{}
};
class ErrorLogArchive : public LogArchive<ELogError>
{
public:
	ErrorLogArchive(int logLevel, const char* tag) : LogArchive(logLevel, tag, "error")
	{}
};
class FatalLogArchive : public LogArchive<ELogFatal>
{
public:
	FatalLogArchive(int logLevel, const char* tag) : LogArchive(logLevel, tag, "fatal")
	{}
};

// 通用的分类日志
template<class T>
class TCategoryLog
{
public:
	static void SetLogLevel(ELogLevel logLevel)
	{
		LogLevel = logLevel;
	}
	static DebugLogArchive debug()
	{
		return (DebugLogArchive(LogLevel, tag));
	}
	static InfoLogArchive info()
	{
		return (InfoLogArchive(LogLevel, tag));
	}
	static WarnLogArchive warn()
	{
		return (WarnLogArchive(LogLevel, tag));
	}
	static ErrorLogArchive err()
	{
		return (ErrorLogArchive(LogLevel, tag));
	}
	static FatalLogArchive fatal()
	{
		return (FatalLogArchive(LogLevel, tag));
	}
private:
	static int LogLevel;
	static const char* tag;
};

// 宏声明的办法
#pragma region DECLARE_IMPL_LOG

#define DECLARE_LOG(class_name) \
	class class_name : public TCategoryLog<class_name> \
	{\
	};

#define IMPLEMENT_LOG(class_name, log_level) \
	int TCategoryLog<class_name>::LogLevel = log_level; \
	const char* TCategoryLog<class_name>::tag = #class_name;

#define DECLARE_IMPL_LOG(class_name, log_level) \
	DECLARE_LOG(class_name) \
	IMPLEMENT_LOG(class_name, log_level)

#pragma endregion


/*
// 手动创建的例子。
class ExampleLog : public TCategoryLog<ExampleLog>
{
};
int TCategoryLog<ExampleLog>::LogLevel = ELogDebug;
const char* TCategoryLog<ExampleLog>::tag = "ExampleLog";

// 用宏声明了一个类
DECLARE_IMPL_LOG(TestLog1, ELogWarning);


*/

#endif