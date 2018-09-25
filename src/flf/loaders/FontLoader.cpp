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

#include <flw/flf/common/Strings.h>
#include <flw/flf/loaders/FontLoader.h>

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
