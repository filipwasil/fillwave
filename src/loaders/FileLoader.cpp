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
  // nothing
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
