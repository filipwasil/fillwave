/*
 * FileLoader.cpp
 *
 *  Created on: 28 Mar, 2014
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


#include <fillwave/loaders/FileLoader.h>
#include <fillwave/Log.h>

#include <fstream>

FLOGINIT("File", FERROR | FFATAL)

namespace flw {
namespace flf {

using namespace std;

FileLoader::FileLoader(const string &rootPath)
    : mRootPath(rootPath) {

}

string FileLoader::getRootPath(string filePath) {
  return (mRootPath + FILLWAVE_OS_SEPRATOR + filePath);
}

/*
 * on Unix systems, the value returned will be the offset in bytes
 * from the beginning of the file, and under Windows,
 * it will be the offset from the beginning of the
 * file for files opened in binary mode.
 * For Windows (and most non-Unix systems),
 * in text mode, there is no direct and immediate
 * mapping between what tellg returns and the number of
 * bytes you must read to get to that position.
 * Under Windows, all you can really count on is that the value
 * will be no less than the number of bytes you have to read
 * (and in most real cases, won't be too much greater,
 * although it can be up to two times more).
 *
 */

void ReadFile(string pFileName, string &fileContent) {
  ifstream ifs(pFileName.c_str(), ios::binary);
  if (!ifs) {
    fLogE("File %s not found", pFileName.c_str());
    return;
  }
  ifs.seekg(0, ios::end);
  auto size = ifs.tellg();
  fileContent.resize(static_cast<size_t>(size));

  ifs.seekg(0, ios::beg);
  ifs.read(&fileContent[0], size);
  ifs.close();
}

void WriteFile(const char *pFileName, string &fileContent) {
  ofstream myfile;
  myfile.open(pFileName);
  myfile << fileContent;
  myfile.close();
}

} /* flf */
} /* flw */
