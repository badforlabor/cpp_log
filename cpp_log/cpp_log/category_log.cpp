// cpp_log.cpp: 定义控制台应用程序的入口点。
//
#include "category_log.h"

// 手动创建的例子。
class ExampleLog : public TCategoryLog<ExampleLog>
{
};
int TCategoryLog<ExampleLog>::LogLevel = ELogDebug;
const char* TCategoryLog<ExampleLog>::tag = "ExampleLog";

// 用宏声明了一个类
DECLARE_IMPL_LOG(TestLog1, ELogWarning);

// 分开声明的例子
DECLARE_LOG(TestLog2)
IMPLEMENT_LOG(TestLog2, ELogWarning);

class ExampleClassA
{
public:
	int a;
	float b;
	char c;
public:
	friend std::string ToString(const ExampleClassA& a)
	{
		return std::string("") + ToString(a.a) + ToString(a.b) + ToString(a.c);
	}
};


int main()
{
	ExampleLog::SetLogLevel(ELogInfo);
	ExampleLog::debug() << 1 << "1.0" << 1.0f << ExampleClassA();
	ExampleLog::info() << 1 << "1.0" << 1.0f << ExampleClassA();
	ExampleLog::warn() << 1 << "1.0" << 1.0f << ExampleClassA();
	ExampleLog::err() << 1 << "1.0" << 1.0f << ExampleClassA();
	ExampleLog::fatal() << 1 << "1.0" << 1.0f << ExampleClassA();

	TestLog1::debug() << 1 << "1.0" << 1.0f << ExampleClassA();
	TestLog1::info() << 1 << "1.0" << 1.0f << ExampleClassA();
	TestLog1::warn() << 1 << "1.0" << 1.0f << ExampleClassA();
	TestLog1::err() << 1 << "1.0" << 1.0f << ExampleClassA();
	TestLog1::fatal() << 1 << "1.0" << 1.0f << ExampleClassA();
	
	TestLog2::debug() << 1 << "1.0" << 1.0f << ExampleClassA();
	TestLog2::info() << 1 << "1.0" << 1.0f << ExampleClassA();
	TestLog2::warn() << 1 << "1.0" << 1.0f << ExampleClassA();
	TestLog2::err() << 1 << "1.0" << 1.0f << ExampleClassA();
	TestLog2::fatal() << 1 << "1.0" << 1.0f << ExampleClassA();
	
	return 0;
}

