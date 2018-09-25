/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <flw/flf/common/Strings.h>
#include <flw/flf/loaders/FileLoader.h>

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

const std::string getStructField(const std::string& structName, int index) {
  std::string strIndex;
  std::stringstream out;
  out << index;
  strIndex = "[" + out.str() + "]";
  out.clear();
  return structName + strIndex;
}

const std::string getNotIndexableName(const std::string& structName, int index) {
  std::string strIndex;
  std::stringstream out;
  out << index;
  strIndex = out.str();
  out.clear();
  return structName + strIndex;
}

std::vector<std::string> &split(const std::string& s, char delim, std::vector<std::string>& elems) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

std::vector<std::string> split(const std::string& s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}

std::string getFilePathOnly(const char* path) {
  if (std::string(path).find(FILLWAVE_OS_SEPRATOR) != std::string::npos) {
    return std::string(path).substr(0, std::string(path).find_last_of(FILLWAVE_OS_SEPRATOR));
  }
  return FILLWAVE_OS_CURRENTDIR;
}

std::string getFileNameOnly(const char* path) {
  if (std::string(path).find(FILLWAVE_OS_SEPRATOR) != std::string::npos) {
    return std::string(path).substr(std::string(path).find_last_of(FILLWAVE_OS_SEPRATOR) + 1, std::string(path).size());
  }
  return std::string(path);
}

} /* flw */
