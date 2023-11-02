#pragma once
#include <string>
#include <algorithm>
#include <cctype> 
#include <cstring>
#include <iostream>

namespace nc
{
	class StringUtils
	{
	public:
		static std::string ToUpper(const std::string& str);
		static std::string ToLower(const std::string& str);
		static bool IsEqualIgnoreCase(const std::string& str1, const std::string& str2);
		static std::string CreateUnique(const std::string& str);
	};
}