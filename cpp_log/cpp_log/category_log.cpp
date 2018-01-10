#include "category_log.h"
#include <map>


static std::map<const char*, void(*)(int)> clsName2Callback;

void CategoryLogConfig::Register(const char* clsName, void(*setLogCallback)(int))
{
	clsName2Callback[clsName] = setLogCallback;
}
void CategoryLogConfig::SetLogLevel(const char* clsName, int logLevel)
{
	auto it = clsName2Callback.find(clsName);
	if (it != clsName2Callback.end())
	{
		it->second(logLevel);
	}
}