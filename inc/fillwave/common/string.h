/*
 * string.h
 *
 *  Created on: 14 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef STRING_H_
#define STRING_H_

#include <string>
#include <vector>
#include <sstream>

namespace fillwave {

std::vector<std::string> split(const std::string &s, char delim);
std::vector<std::string> &split(
		const std::string &s,
		char delim,
		std::vector<std::string> &elems);
std::string getStructField(
		std::string structName,
		std::string fieldName,
		int index);
std::string getStructField(std::string structName, int index);
std::string getNotIndexableName(std::string structName, int index);

template<typename T>
std::string to_string(T value) {
	std::ostringstream os;
	os << value;
	return os.str();
}

std::string getFilePathOnly(const char* path);
std::string getFileNameOnly(const char* path);

} /* fillwave */

#endif /* STRING_H_ */
