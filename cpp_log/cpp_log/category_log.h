#pragma once
#ifndef _CATEGORY_LOG_H_
#define _CATEGORY_LOG_H_

#include <iostream>
#include "string_util.h"

/************************************************************************/
/* ini 配置日志分级                                                     */
/************************************************************************/
class CategoryLogConfig
{
public:
	static void Register(const char* clsName, void(*setLogCallback)(int));
	static void SetLogLevel(const char* clsName, int logLevel);
};
template<class T>
class CategoryLogConfigAutoRegister
{
public:
	CategoryLogConfigAutoRegister()
	{
		CategoryLogConfig::Register(T::GetTag(), T::SetLogLevel);
	}
};

/************************************************************************/
/* 日志流			                                                    */
/************************************************************************/
extern void CategoryLogOutput(const char*, const char* classTag, const char* logTag, const char* content);
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
			CategoryLogOutput(" [%s][%s]: %s", ClassTag, LogTag, str.c_str());
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

/************************************************************************/
/* 通用的分类日志。                                                     */
/************************************************************************/
template<class T>
class TCategoryLog
{
public:
	static const char* GetTag()
	{
		return tag;
	}
	static void SetLogLevel(int logLevel)
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
	static CategoryLogConfigAutoRegister<T> AutoReg;
};

// 宏声明的办法。
#pragma region DECLARE_IMPL_LOG

#define DECLARE_LOG(class_name) \
	class class_name : public TCategoryLog<class_name> \
	{\
	};

#define IMPLEMENT_LOG(class_name, log_level) \
	template<> int TCategoryLog<class_name>::LogLevel = log_level; \
	template<> const char* TCategoryLog<class_name>::tag = #class_name; \
	template<> CategoryLogConfigAutoRegister<class_name> TCategoryLog<class_name>::AutoReg;

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