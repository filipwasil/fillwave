/*
 * FileLoader.cpp
 *
 *  Created on: 28 Mar, 2014
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


#include <fillwave/loaders/FileLoader.h>
#include <fillwave/extras/Log.h>
#include <fstream>

FLOGINIT("File", FERROR | FFATAL)

namespace fillwave {
namespace loader {

using namespace std;

FileLoader::FileLoader(const string& rootPath):mRootPath(rootPath) {

}


FileLoader::~FileLoader() {

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

void ReadFile(string pFileName, string& fileContent) {
   ifstream ifs(pFileName.c_str(), ios::binary);
   if(ifs) {
      ifs.seekg(0,ios::end);
      size_t size = ifs.tellg();
      fileContent.resize(size);

      ifs.seekg(0, ios::beg);
      ifs.read(&fileContent[0],size);
      ifs.close();
   } else {
      FLOG_ERROR("File %s not found",pFileName.c_str());
   }
}

void WriteFile( const char* pFileName, string& fileContent) {
   ofstream myfile;
   myfile.open (pFileName);
   myfile << fileContent;
   myfile.close();
}

} /* loader */
} /* fillwave */
