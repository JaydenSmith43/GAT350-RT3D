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
		static uint32_t unique = 1;

		return str + std::to_string(unique++);
	}

	// return the number at the end of a string "name43" -> 43, if there are no digits return -1
	int StringUtils::GetTrailingNumber(const std::string& str)
	{
		// if the string is empty return -1
		if (str.empty()) return -1;

		// check from the end of the string for characters that are digits, add digit to strNumber
		// if character is not digit, then exit
		std::string strNumber;
		for (size_t i = str.size() - 1; i >= 0; i--)
		{
			if (std::isdigit(str[i])) strNumber = str[i] + strNumber;
			else break;
		}

		// convert strNumber to a number if not empty
		return (!strNumber.empty()) ? std::stoi(strNumber) : -1;
	}

	// remove any digit characters from the end of the string "name43" -> "name"
	std::string StringUtils::RemoveTrailingNumber(const std::string& str)
	{
		if (str.empty()) return "";

		// set result string to str parameter
		// start at the end of the string and remove any characters that are digits
		// if character is not a digit, then exit
		std::string result = str;
		for (size_t i = str.size() - 1; i >= 0; i--)
		{
			if (std::isdigit(str[i])) result.pop_back();
			else break;
		}

		// return string without trailing number
		return result;
	}

}

