#ifndef _STRINGLIST_H_
#define _STRINGLIST_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "Constants.h"

/*
For holding all the words from the file the user specified
*/
namespace ws {
	class StringList {
	public:
		StringList();
		bool populate(std::string& relativePath);
		bool empty() const;
		std::string& at(unsigned i);
		void remove(std::string& str);
		std::string& getRandomString();
		void clear();
	private:
		std::vector<std::string> Strings;
		void convertAndCheckWords();
	};
}

#endif