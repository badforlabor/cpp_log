#ifndef _VAR_ARGS_H_
#define _VAR_ARGS_H_

#include "string_util.h"

// printf只支持基础数据类型，凡是非基础数据类型，都自己转一下。
static inline unsigned int			CheckVA(unsigned int dw) { return dw; }
static inline unsigned char			CheckVA(unsigned char b) { return b; }
static inline int			CheckVA(int i) { return i; }
static inline unsigned long long int			CheckVA(unsigned long long int qw) { return qw; }
static inline long long int		CheckVA(long long int sqw) { return sqw; }
static inline float		CheckVA(float d) { return d; }
static inline double		CheckVA(double d) { return d; }
static inline long		CheckVA(long d) { return d; }
static inline long		CheckVA(unsigned long d) { return d; }
static inline char			CheckVA(char c) { return c; }
static inline const char*			CheckVA(const char* c) { return c; }
static inline void*			CheckVA(char* s) { return (void*)s; }
static inline bool		CheckVA(bool b) { return b; }

template<class T1, class T2>
T2 type_to_type(const T1& t1)
{
	static_assert(false, "需要类型转换");
}
template<class T1>
std::string type_to_type(const T1& t1)
{
	return ToString(t1);
}

template<class T1, class T2, class T3>
std::string printf(const char* fmt, T1 t1, T2 t2, T3 t3)
{
	T1 tt1 = CheckVA(t1);
	T2 tt2 = CheckVA(t2);
	T3 tt3 = CheckVA(t3);
	
	/*
		计划是：解析fmt：
			如果解析到%s，那么执行 type_to_string(tn)
			如果解析到%d，那么执行 type_to_int(tn)
			...
		但是，由于写法太不优雅了。所以，暂时先延后把。
	*/

	return type_to_type(tt1) + type_to_type(tt2) + type_to_type(tt3);
}
template<class T1, class T2>
std::string printf(const char* fmt, const T1& t1, const T2& t2)
{
	printf(fmt, t1, t2, 0);
}
template<class T1>
std::string printf(const char* fmt, const T1& t1)
{
	printf(fmt, t1, 0, 0);
}

extern void string_replace(std::string&s1, const std::string&s2, const std::string&s3);
// 支持格式：logf("param1:{0}, param2:{1}, param1:{0}", p1, p2);
extern std::string Logf(int n, const char* fmt, const char* p1, const char* p2, const char* p3);

#endif