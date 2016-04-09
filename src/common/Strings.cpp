/*
 * string.cpp
 *
 *  Created on: 14 Apr 2014
 *      Author: Filip Wasil
 */

#include <fillwave/common/Strings.h>
#include <fillwave/loaders/FileLoader.h>
#include <fillwave/Log.h>

FLOGINIT("String", FERROR | FFATAL)

namespace fillwave {

std::vector<std::string> &split(
   const std::string &s,
   char delim,
   std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

std::string getStructField(
   std::string structName,
   std::string fieldName,
   int index) {
	std::string strIndex;
	std::stringstream out;
	out << index;
	strIndex = "[" + out.str() + "]";
	if (fieldName != "") {
		strIndex = strIndex + "." + fieldName;
	}

	out.clear();
	return structName + strIndex;
}

std::string getStructField(std::string structName, int index) {
	std::string strIndex;
	std::stringstream out;
	out << index;
	strIndex = "[" + out.str() + "]";
	out.clear();
	return structName + strIndex;
}

std::string getNotIndexableName(std::string structName, int index) {
	std::string strIndex;
	std::stringstream out;
	out << index;
	strIndex = out.str();
	out.clear();
	return structName + strIndex;
}

std::string getFilePathOnly(const char* path) {
	if (std::string(path).find(FILLWAVE_OS_SEPRATOR) != std::string::npos) {
		return std::string(path).substr(0,
		                                std::string(path).find_last_of(FILLWAVE_OS_SEPRATOR));
	} else {
		return FILLWAVE_OS_CURRENTDIR;
	}
}

std::string getFileNameOnly(const char* path) {
	if (std::string(path).find(FILLWAVE_OS_SEPRATOR) != std::string::npos) {
		return std::string(path).substr(
		          std::string(path).find_last_of(FILLWAVE_OS_SEPRATOR) + 1,
		          std::string(path).size());
	} else {
		return std::string(path);
	}
}

} /* fillwave */
