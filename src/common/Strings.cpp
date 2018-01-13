/*
 * Copyright (c) 2018, Fillwave developers
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
