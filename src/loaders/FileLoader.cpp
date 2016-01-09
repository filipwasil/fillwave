/*
 * FileLoader.cpp
 *
 *  Created on: 28 Mar, 2014
 *      Author: Filip Wasil
 */

#include <fillwave/loaders/FileLoader.h>
#include <fillwave/Log.h>
#include <fstream>

FLOGINIT("File", FERROR | FFATAL)

namespace fillwave {
namespace framework {

using namespace std;

FileLoader::FileLoader(const string& rootPath)
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

void ReadFile(string pFileName, string& fileContent) {
	ifstream ifs(pFileName.c_str(), ios::binary);
	if (ifs) {
		ifs.seekg(0, ios::end);
		size_t size = ifs.tellg();
		fileContent.resize(size);

		ifs.seekg(0, ios::beg);
		ifs.read(&fileContent[0], size);
		ifs.close();
	} else {
		FLOG_ERROR("File %s not found", pFileName.c_str());
	}
}

void WriteFile(const char* pFileName, string& fileContent) {
	ofstream myfile;
	myfile.open(pFileName);
	myfile << fileContent;
	myfile.close();
}

} /* framework */
} /* fillwave */
