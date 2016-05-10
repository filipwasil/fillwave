/*
 * AndroidLoader.h
 *
 *  Created on: 18 Mar, 2014
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
