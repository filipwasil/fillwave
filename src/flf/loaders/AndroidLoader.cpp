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

#ifdef __ANDROID__

#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

// for native asset manager
#include <sys/types.h>
#include <flw/Log.h>
#include <flw/flf/loaders/AndroidLoader.h>

FLOGINIT("Android loader", FERROR | FFATAL)

namespace flw {
namespace flf {

ANativeActivity* gActivity;

void androidSetActivity(ANativeActivity* activity) {
  gActivity = activity;
}

bool androidExtractAll() {
  AAssetDir* assetDir = AAssetManager_openDir(gActivity->assetManager, "");
  const char* filename = (const char*)NULL;
  std::string assetContent;
  while ((filename = AAssetDir_getNextFileName(assetDir)) != NULL) {
    std::string newPath = androidGetPath(filename);
    AAsset* asset = AAssetManager_open(gActivity->assetManager, filename,
                            AASSET_MODE_STREAMING);
    fLogD("File %s opened for extraction ...", filename );
    // Find size
    off_t assetSize = AAsset_getLength(asset);

    // Prepare input buffer
    assetContent.resize(assetSize);

    // Store input buffer
    AAsset_read(asset, &assetContent[0], assetSize);

    // Close
    AAsset_close(asset);

    // Check if file exists
    std::ifstream f(newPath.c_str());
    if (f.good()) {
      f.close();
      fLogD("Asset %s already extracted", filename);
    } else {
      // Prepare output buffer
      std::ofstream assetExtracted(newPath.c_str(),
                          std::ios::out | std::ios::binary);
      if (!assetExtracted) {
        fLogE("File %s not extracted", newPath.c_str());
        return false;
      }

      // Write output buffer into a file
      assetExtracted.write(assetContent.c_str(), assetSize);
      assetExtracted.close();

      fLogD("File %s extracted", filename);
    }
  }
  AAssetDir_close(assetDir);
    return true;
}

void androidRead(const char* pFileName, char** ppContent, unsigned int* pSize) {
  assert( gActivity->assetManager );

  AAsset* pFile = AAssetManager_open(gActivity->assetManager, pFileName,
                          AASSET_MODE_STREAMING);

  if (pFile != NULL) {

    off_t fileSize = AAsset_getLength(pFile);

    std::string path = androidGetPath(pFileName);
    char* pData = new char[fileSize];
    AAsset_read(pFile, pData, fileSize);

    *ppContent = new char[fileSize];

    memcpy(*ppContent, pData, fileSize);
    *pSize = fileSize;

    fLogD("File %s length %d", pFileName, *pSize);
    delete [] pData;
    AAsset_close(pFile);
  }
}

void androidReadToString(const char* pFileName, std::string& fileContent) {
  assert( gActivity->assetManager );

  AAsset* pFile = AAssetManager_open(gActivity->assetManager, pFileName,
                          AASSET_MODE_UNKNOWN);

  if (pFile != NULL) {
    off_t fileSize = AAsset_getLength(pFile);

    fileContent.resize(fileSize);
    //char* pData = new char[fileSize];
    AAsset_read(pFile, &fileContent[0], fileSize);

    AAsset_close(pFile);
    fLogD("File %s found", pFileName);
  } else {
    fLogE("File %s not found", pFileName);
  }
}

bool androidExtract( const std::string& name ) {
  const char* pFile = name.c_str();
  std::string newPath = androidGetPath(pFile);
  //AAssetDir* a;
  if ( androidExtracted(name.c_str()) ) {
    fLogD("File %s already extracted", name.c_str());
    return true;
  }

  AAsset* asset = AAssetManager_open(gActivity->assetManager, name.c_str(),
                          AASSET_MODE_STREAMING);
  std::string assetContent;

  if (asset != NULL) {
    // Find size
    off_t assetSize = AAsset_getLength(asset);

    // Prepare input buffer
    assetContent.resize(assetSize);

    // Store input buffer
    AAsset_read(asset, &assetContent[0], assetSize);

    // Close
    AAsset_close(asset);

    // Prepare output buffer
    std::ofstream assetExtracted(newPath.c_str(),
                        std::ios::out | std::ios::binary);
    if (!assetExtracted) {
      fLogE("File %s not extracted", newPath.c_str());
      return false;
    }

    // Write output buffer into a file
    assetExtracted.write(assetContent.c_str(), assetSize);
    assetExtracted.close();

    fLogD("File extracted");
    return true;
  } else {
    fLogE("File %s not extracted. Returning empty string", name.c_str());
    return false;
  }
}

std::string androidGetPath(const char* pFile) {
  return std::string(std::string(gActivity->internalDataPath) + "/" + std::string(
                 pFile));
}

bool androidExtracted(const char* pFile) {
  FILE* file = ::fopen( androidGetPath(pFile).c_str(), "rb");
  if (!file) {
    AAsset* asset = AAssetManager_open(gActivity->assetManager, pFile,
                            AASSET_MODE_UNKNOWN);
    if (!asset) {
      fLogE("Could not find %s in asset manager", pFile);
    } else {
      fLogD("%s is not extracted", pFile);
    }
    return false;
  } else {
    ::fclose(file);
    return true;
  }
}

} /* flf */
} /* flw */

#endif /* __ANDROID__ */
