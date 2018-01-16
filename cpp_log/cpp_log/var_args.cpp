#include "var_args.h"

void string_replace(std::string&s1, const std::string&s2, const std::string&s3)
{
	std::string::size_type pos = 0;
	std::string::size_type a = s2.size();
	std::string::size_type b = s3.size();
	while ((pos = s1.find(s2, pos)) != std::string::npos)
	{
		s1.replace(pos, a, s3);
		pos += b;
	}
}

std::string Logf(int n, const char* fmt, const char* p1, const char* p2, const char* p3)
{
	std::string ret(fmt);

	const char* parray[] = { p1,p2,p3 };

	for (int i = 0; i < n; i++)
	{
		string_replace(ret, "{0}", parray[i]);
	}
	return ret;
}