
#ifdef __ANDROID__

#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

// for native asset manager
#include <sys/types.h>
#include <fillwave/extras/Log.h>
#include <fillwave/loaders/AndroidLoader.h>

FLOGINIT("Android loader", FERROR | FFATAL)

namespace fillwave {
namespace loader {

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
      AAsset* asset = AAssetManager_open(gActivity->assetManager, filename, AASSET_MODE_STREAMING);
      FLOG_DEBUG("File %s opened for extraction ...", filename );
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
          FLOG_DEBUG("Asset %s already extracted", filename);
      } else {
         // Prepare output buffer
         std::ofstream assetExtracted(newPath.c_str(),
               std::ios::out | std::ios::binary);
         if (!assetExtracted) {
           FLOG_ERROR("File %s not extracted", newPath.c_str());
           return false;
         }

         // Write output buffer into a file
         assetExtracted.write(assetContent.c_str(), assetSize);
         assetExtracted.close();

        FLOG_DEBUG("File %s extracted", filename);
      }
   }
   return true;
   AAssetDir_close(assetDir);
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

      FLOG_DEBUG("File %s length %d", pFileName, *pSize);
      delete pData;

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
      char* pData = new char[fileSize];
      AAsset_read(pFile, &fileContent[0], fileSize);

      AAsset_close(pFile);
      FLOG_DEBUG("File %s found", pFileName);
   } else {
      FLOG_ERROR("File %s not found", pFileName);
   }
}

bool androidExtract( const std::string& name ) {
   const char* pFile = name.c_str();
   std::string newPath = androidGetPath(pFile);
   AAssetDir* a;
   if ( androidExtracted(name.c_str()) ) {
      FLOG_DEBUG("File %s already extracted", name.c_str());
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
         FLOG_ERROR("File %s not extracted", newPath.c_str());
         return false;
      }

      // Write output buffer into a file
      assetExtracted.write(assetContent.c_str(), assetSize);
      assetExtracted.close();

      FLOG_DEBUG("File extracted");
      return true;
   } else {
      FLOG_ERROR("File %s not extracted. Returning empty string", name.c_str());
      return false;
   }
}

std::string androidGetPath(const char* pFile) {
   return std::string(std::string(gActivity->internalDataPath) + "/" + std::string(pFile));
}

bool androidExtracted(const char* pFile) {
   FILE* file = ::fopen( androidGetPath(pFile).c_str(), "rb");
   if (!file) {
      AAsset* asset = AAssetManager_open(gActivity->assetManager, pFile, AASSET_MODE_UNKNOWN);
      if (!asset) {
         FLOG_ERROR("Could not find %s in asset manager", pFile);
      } else {
         FLOG_DEBUG("%s is not extracted", pFile);
      }
      return false;
   } else {
      ::fclose(file);
      return true;
   }
}

} /* loader */
} /* fillwave */

#endif /* __ANDROID__ */
