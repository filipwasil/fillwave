/*
 * FontLoader.cpp
 *
 *  Created on: Aug 9, 2014
 *      Author: filip
 */

#include <fillwave/extras/Log.h>
#include <fillwave/extras/string.h>
#include <fillwave/loaders/FontLoader.h>

FLOGINIT("FontLoader", FERROR | FFATAL)

namespace fillwave {
namespace loader {

void FontLoader::load(std::string name) {
	std::vector<std::string> splitted = strings::split(name, '/');
	if (splitted.size()) {
		(*(splitted.end() - 1)).c_str();
	}
	std::string pngPath = name + ".png";
	std::string metaPath = name + ".meta";
	/* We can use any fo we like */
	if (generateFontMetadata((name + ".ttf").c_str(), pngPath.c_str(),
			metaPath.c_str())) {
		std::string ttfPath = "/usr/share/fonts/truetype/freefont/"
				+ (*(splitted.end() - 1)) + ".ttf";
		/* Well, if we do not have it, we look in /usr/share/fonts/truetype/freefont/*/
		generateFontMetadata(ttfPath.c_str(), pngPath.c_str(), metaPath.c_str());
	}
}

} /* loader */
} /* fillwave */
