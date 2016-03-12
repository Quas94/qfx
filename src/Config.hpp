#pragma once

/**
* Class which facilitates the reading and writing of conf files. Expected format is
* similar to that of Java's .properties files.
*
* Author: Quasar
* Date:   11/3/16
*/
#include <string>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

namespace Qfx {

	class ConfigException : exception {

	public:

		const char * what() const noexcept;

	};

	class Config {

	private:

		// name of the file that this Config represents
		string filename;

		// map to store key-value pairs from the config file
		map<string, string> mappings;

		// function to trim whitespace from both sides of the string
		string& trim(string& input) const;

	public:

		static const char COMMENT_PREFIX = '#';
		static const char EQUALS_SIGN = '=';
		static const string ACCOUNT_ID;
		static const string API_KEY;

		/**
		* Constructs a new Config object and accepts the filename as a parameter.
		* Immediately attempts to load the file and read in the properties.
		*/
		Config(string filename);

		const string operator[](const char* cstr);
		const string operator[](const string str);

	};
}