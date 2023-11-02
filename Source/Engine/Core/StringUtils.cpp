#include "StringUtils.h"

namespace nc
{
	std::string StringUtils::ToUpper(const std::string& str)
	{
		std::string str2 = str;
		
		std::transform(str2.begin(), str2.end(), str2.begin(), ::toupper);
		return str2;
	}

	std::string StringUtils::ToLower(const std::string& str)
	{
		std::string str2 = str;

		std::transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
		return str2;
	}

	bool StringUtils::IsEqualIgnoreCase(const std::string& str1, const std::string& str2)
	{
		std::string str1_input = ToLower(str1);
		std::string str2_input = ToLower(str2);

		int res = str1_input.compare(str2_input);

		return res == 0;
	}

	std::string StringUtils::CreateUnique(const std::string& str)
	{
		static uint32_t unique = 0;

		return str + std::to_string(unique++);
	}
}

