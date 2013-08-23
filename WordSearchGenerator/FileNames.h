#ifndef _FILENAMES_H_
#define _FILENAMES_H_

#include <string>

std::string getOnlyTheFileName(const std::string& str);
std::string getFileNameWithExt(const std::string& str);
std::string getFilePathWithoutExt(const std::string& str);
std::string getFilePathOnly(const std::string& str);

#endif