/**
 * Class which facilitates the reading and writing of conf files. Expected format is
 * similar to that of Java's .properties files.
 *
 * Author: Quasar
 * Date:   11/3/16
 */
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>
#include <fstream>
#include <map>

#include "Config.hpp"

using namespace std;

namespace Qfx {

	ConfigException _ConfigException;

	const char * ConfigException::what() const noexcept {
		return "ConfigException encountered: Check config file!";
	};

	string& Config::trim(string& s) const {
		s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
		s.erase(find_if(s.rbegin(), s.rend(), not1(std::ptr_fun<int, int>(isspace))).base(), s.end());
		return s;
	}

	// config constants
	const string Config::ACCOUNT_ID = "account_id";
	const string Config::API_KEY = "api_key";

	Config::Config(string filename) : filename(filename) {
		ifstream file;
		file.open(filename);
		string line;
		while (getline(file, line)) {
			if (line.length() == 0) continue; // empty line
			if (line.at(0) == Config::COMMENT_PREFIX) continue; // comment line

			// try to find the equals character
			size_t equalsPos = line.find(Config::EQUALS_SIGN);
			if (equalsPos == string::npos) {
				throw _ConfigException;
			}
			string left = trim(line.substr(0, equalsPos));
			string right = trim(line.substr(equalsPos + 1, string::npos));
			// add to mapping
			mappings[left] = right;
			// cout << mappings[left] << endl;
		}
		file.close();
	}

	const string Config::operator[](const string str) {
		return mappings[str];
	}

	const string Config::operator[](const char* cstr) {
		string str = cstr;
		return operator[](str);
	}
}
