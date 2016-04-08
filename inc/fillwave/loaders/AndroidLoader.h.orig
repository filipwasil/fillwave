/*
 * AndroidLoader.h
 *
 *  Created on: 18 Mar, 2014
 *      Author: Filip Wasil
 */

#ifdef __ANDROID__

#ifndef ANDROIDLOADER_H_
#define ANDROIDLOADER_H_

// For native asset manager
#include <sys/types.h>
#include <android/native_activity.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <string>

namespace fillwave {
	namespace framework {

		void androidSetActivity(ANativeActivity* activity);

// Read the contents of the give file return the content and the file size
		void androidRead( const char* FileName, char** Content, unsigned int* Size );
		void androidReadToString( const char* pFileName, std::string& fileContent );
		bool androidExtracted( const char* pFile );
		bool androidExtract( const std::string& name );
		std::string androidGetPath( const char* pFile );
		bool androidExtractAll();

	} /* framework */
} /* fillwave */

#endif /* ANDROIDLOADER_H_ */

#endif /* __ANDROID__ */
