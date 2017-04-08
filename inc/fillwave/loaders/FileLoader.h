#pragma once

/*
 * FileLoader.h
 *
 *  Created on: 18 Mar, 2014
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Filip Wasil
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

#include <string>

#ifdef __linux__
#define FILLWAVE_OS_SEPRATOR "/"
#define FILLWAVE_OS_CURRENTDIR "./"
#elif _WIN32
#define FILLWAVE_OS_SEPRATOR "\\"
#define FILLWAVE_OS_CURRENTDIR "./"
#elif __APPLE__
#define FILLWAVE_OS_SEPRATOR "/"
#define FILLWAVE_OS_CURRENTDIR "./"
#endif

namespace flw {
namespace flf {

/*! \class FileLoader
 * \brief Loads files.
 */

class FileLoader {
public:
  FileLoader(const std::string &rootPath);

  ~FileLoader() = default;

  std::string getRootPath(std::string filePath = "");

private:
  std::string mRootPath;
};

void WriteFile(const char *pFileName, std::string &fileContent);

void ReadFile(std::string pFileName, std::string &fileContent);

std::string ReadFile(std::string fileName);

} /* frf */
} /* flf */

