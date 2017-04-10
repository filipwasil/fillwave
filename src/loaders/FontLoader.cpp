/*
 * FontLoader.cpp
 *
 *  Created on: Aug 9, 2014
 *      Author: filip
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


#include <fillwave/common/Strings.h>
#include <fillwave/Log.h>
#include <fillwave/loaders/FontLoader.h>


namespace flw {
namespace flf {

void FontLoader::load(std::string name) {
  std::vector<std::string> splitted = split(name, '/');
  if (splitted.size()) {
    (*(splitted.end() - 1)).c_str();
  }
  std::string pngPath = name + ".png";
  std::string metaPath = name + ".meta";
  /* We can use any fo we like */
  if (generateFontMetadata((name + ".ttf").c_str(), pngPath.c_str(), metaPath.c_str())) {
    std::string ttfPath = "/usr/share/fonts/truetype/freefont/" + (*(splitted.end() - 1)) + ".ttf";
    /* Well, if we do not have it, we look in /usr/share/fonts/truetype/freefont/*/
    generateFontMetadata(ttfPath.c_str(), pngPath.c_str(), metaPath.c_str());
  }
}

} /* flf */
} /* flw */
