/*
 * string.cpp
 *
 *  Created on: 14 Apr 2014
 *      Author: Filip Wasil
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * filip.wasil@gmail.com
 *
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
