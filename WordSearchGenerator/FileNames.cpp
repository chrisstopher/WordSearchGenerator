#include "FileNames.h"

/*
Returns the filename without the path prefix and extension suffix
*/
std::string getOnlyTheFileName(const std::string& str) {
	size_t path = str.find_last_of("/\\");
	size_t ext = str.find_last_of(".");
	unsigned sizeOfFileName = (ext - 1) - path;
	return str.substr(path + 1, sizeOfFileName);
}

/*
Returns the filename without the path prefix
*/
std::string getFileNameWithExt(const std::string& str) {
	size_t path = str.find_last_of("/\\");
	return str.substr(path + 1);
}

/*
Returns the filename without the extension suffix
*/
std::string getFilePathWithoutExt(const std::string& str) {
	size_t ext = str.find_last_of(".");
	return str.substr(0, ext);
}

/*
Returns the path prefix
*/
std::string getFilePathOnly(const std::string& str) {
	size_t path = str.find_last_of("/\\");
	return str.substr(0, path + 1);
}