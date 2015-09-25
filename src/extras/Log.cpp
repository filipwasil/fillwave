/*
 * Log.cpp
 *
 *  Created on: 1 mar 2015
 *      Author: filip
 */

#include <fillwave/extras/Log.h>

FLOGINIT("Log", FERROR | FFATAL)

namespace fillwave {

std::string logFilePath = "";
bool fileValid = false;

std::string getLogPath() {
	return logFilePath;
}

void setLogPath(std::string path) {
	FILE *fp = fopen(path.c_str(), "w");
	if (fp) {
		fclose(fp);
		fileValid = true;
		logFilePath = path;
	} else {
		FLOG_ERROR("Can not write to %s file", path.c_str());
		fileValid = false;
	}
}

bool isFileValid() {
	return fileValid;
}

void setFileInvalid() {
	fileValid = false;
}

} /* fillwave */

