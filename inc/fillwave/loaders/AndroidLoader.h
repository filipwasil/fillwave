/*
 * AndroidLoader.h
 *
 *  Created on: 18 Mar, 2014
 *      Author: Filip Wasil
 */

#ifdef __ANDROID__

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

#ifndef ANDROIDLOADER_H_
#define ANDROIDLOADER_H_

// For native asset manager
#include <sys/types.h>
#include <android/native_activity.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <string>

namespace fillwave {
namespace loader {

void androidSetActivity(ANativeActivity* activity);

// Read the contents of the give file return the content and the file size
void androidRead( const char* FileName, char** Content, unsigned int* Size );
void androidReadToString( const char* pFileName, std::string& fileContent );
bool androidExtracted( const char* pFile );
bool androidExtract( const std::string& name );
std::string androidGetPath( const char* pFile );
bool androidExtractAll();

} /* loader */
} /* fillwave */

#endif /* ANDROIDLOADER_H_ */

#endif /* __ANDROID__ */
