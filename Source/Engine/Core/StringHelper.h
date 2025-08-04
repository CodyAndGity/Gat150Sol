#pragma once
#include <string>
namespace bonzai {
	inline std::string toLower(const std::string& str) {
		std::string result = str;
		// Convert each character to lowercase
		for (char& c : result) {
			c = tolower(c);
		}
		return result;
	}

	inline std::string toUpper(const std::string& str) {
		std::string result = str;
		// Convert each character to uppercase
		for (char& c : result) {
			c = toupper(c);
		}
		return result;
	}

};