/*
 * string.cpp
 *
 *  Created on: 14 Apr 2014
 *      Author: Filip Wasil
 */

#include <fillwave/extras/Log.h>
#include <fillwave/extras/string.h>

FLOGINIT("String", FERROR | FFATAL)

namespace fillwave {
namespace strings {

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

}
}
