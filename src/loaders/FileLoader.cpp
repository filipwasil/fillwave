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

#include <fillwave/PlatformSW.h>
#include <fillwave/loaders/FileLoader.h>
#include <fillwave/Log.h>
#include <fstream>

FLOGINIT_DEFAULT()

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

void ReadFile(string fileName, string& fileContent) {
  ifstream ifs(fileName.c_str(), ios::binary);
  if (!ifs) {
    fLogE("File %s not found", fileName.c_str());
    return;
  }
  ifs.seekg(0, ios::end);
  auto size = ifs.tellg();
  fileContent.resize(static_cast<size_t>(size));

  ifs.seekg(0, ios::beg);
  ifs.read(&fileContent[0], size);
  ifs.close();
}

void WriteFile(const char* fileName, const std::string& fileContent, bool printOut) {
  std::ofstream file (fileName);
  if (!file.is_open()) {
    fLogE("File %s can not be created", fileName);
    return;
  }
  file << fileContent << endl;
  if (printOut) {
    fLogE("Shader created: %s\n%s", fileName, fileContent.c_str());
  }
  file.close();
}

} /* flf */
} /* flw */
