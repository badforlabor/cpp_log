#pragma once

#ifndef _STRING_UTIL_H_
#define _STRING_UTIL_H_

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

#endif