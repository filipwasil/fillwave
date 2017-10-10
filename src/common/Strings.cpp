/*
 * string.cpp
 *
 *  Created on: 14 Apr 2014
 *      Author: Filip Wasil
 */

#include <fillwave/common/Strings.h>
#include <fillwave/loaders/FileLoader.h>

namespace flw {

std::string getStructField(std::string structName, std::string fieldName, int index) {
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

std::string getFilePathOnly(const char *path) {
  if (std::string(path).find(FILLWAVE_OS_SEPRATOR) != std::string::npos) {
    return std::string(path).substr(0, std::string(path).find_last_of(FILLWAVE_OS_SEPRATOR));
  }
  return FILLWAVE_OS_CURRENTDIR;
}

std::string getFileNameOnly(const char *path) {
  if (std::string(path).find(FILLWAVE_OS_SEPRATOR) != std::string::npos) {
    return std::string(path).substr(std::string(path).find_last_of(FILLWAVE_OS_SEPRATOR) + 1, std::string(path).size());
  }
  return std::string(path);
}

} /* flw */
