/*
 * FontLoader.cpp
 *
 *  Created on: Aug 9, 2014
 *      Author: filip
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

#include <fillwave/extras/Log.h>
#include <fillwave/extras/string.h>
#include <fillwave/loaders/FontLoader.h>

FLOGINIT("FontLoader", FERROR | FFATAL)

namespace fillwave {
namespace loader {

FontLoader::FontLoader(){

}

FontLoader::~FontLoader() {

}

void FontLoader::load(std::string name) {
   std::vector<std::string> splitted = strings::split(name, '/');
   if (splitted.size()) {
      (*(splitted.end()-1)).c_str();
   }
   std::string pngPath = name + ".png";
   std::string metaPath = name + ".meta";
   /* We can use any fo we like */
   if (generateFontMetadata((name + ".ttf").c_str(), pngPath.c_str(), metaPath.c_str())) {
      std::string ttfPath = "/usr/share/fonts/truetype/freefont/" + (*(splitted.end()-1)) + ".ttf";
      /* Well, if we do not have it, we look in /usr/share/fonts/truetype/freefont/*/
      generateFontMetadata(ttfPath.c_str(), pngPath.c_str(), metaPath.c_str());
   }
}

} /* loader */
} /* fillwave */
