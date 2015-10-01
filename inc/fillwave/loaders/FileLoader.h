/*
 * FileLoader.h
 *
 *  Created on: 18 Mar, 2014
 *      Author: Filip Wasil
 */

#ifndef FILE_H_
#define FILE_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
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

namespace fillwave {
namespace loader {

using namespace std;

/*! \class FileLoader
 * \brief Loads files.
 */

class FileLoader {
public:
   FileLoader(const std::string& rootPath);

   ~FileLoader();

   std::string getRootPath(std::string filePath = "");

private:
   std::string mRootPath;
};

void WriteFile(const char* pFileName, std::string& fileContent);
void ReadFile( std::string pFileName, std::string& fileContent);
string ReadFile(string fileName);

} /* std */
} /* fillwave */

#endif /* FILE_H_ */
