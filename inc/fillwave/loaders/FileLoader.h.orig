/*
 * FileLoader.h
 *
 *  Created on: 18 Mar, 2014
 *      Author: Filip Wasil
 */

#ifndef FILE_H_
#define FILE_H_

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
namespace framework {

/*! \class FileLoader
 * \brief Loads files.
 */

class FileLoader {
public:
	FileLoader(const std::string& rootPath);

	~FileLoader() = default;

	std::string getRootPath(std::string filePath = "");

private:
	std::string mRootPath;
};

void WriteFile(const char* pFileName, std::string& fileContent);
void ReadFile(std::string pFileName, std::string& fileContent);
std::string ReadFile(std::string fileName);

} /* framework */
} /* fillwave */

#endif /* FILE_H_ */
