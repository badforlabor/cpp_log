// cpp_log.cpp: �������̨Ӧ�ó������ڵ㡣
//
#include "category_log.h"

static void SetLogLevel(int logLevel)
{
}


// �ֶ����������ӡ�
class ExampleLog : public TCategoryLog<ExampleLog>
{
};
int TCategoryLog<ExampleLog>::LogLevel = ELogDebug;
const char* TCategoryLog<ExampleLog>::tag = "ExampleLog";
CategoryLogConfigAutoRegister<ExampleLog> TCategoryLog<ExampleLog>::AutoReg;

// �ú�������һ����
DECLARE_IMPL_LOG(TestLog1, ELogWarning);

// �ֿ�����������
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
	// ��������֮�󣬶�ȡini��Ȼ��ѭ��ִ�� CategoryLogConfig::SetLogLevel(key, logLevel);
	CategoryLogConfig::SetLogLevel(TestLog2::GetTag(), ELogDebug);

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

