/******************************************************************************\
| OpenGL 4 Example Code.                                                       |
| Accompanies written series "Anton's OpenGL 4 Tutorials"                      |
| Email: anton at antongerdelan dot net                                        |
| First version 5 Feb 2014                                                     |
| Copyright Dr Anton Gerdelan, Trinity College Dublin, Ireland.                |
| See individual libraries and assets for respective legal notices             |
|******************************************************************************|
| Font Atlas Generator example                                                 |
| Uses Sean Barrett's STB_IMAGE_WRITE library for writing to PNG               |
\******************************************************************************/

/*! \class Font
 * \brief Representation of freetype font.
 */

#ifndef FONT_GENERATOR_H_
#define FONT_GENERATOR_H_

#include <fillwave/OpenGL.h>
#include <memory>

namespace fillwave {

struct Font {
   std::string mName;
   GLfloat mOffsets[256];
   GLfloat mWidths[256];
   const GLint mAtlasColumns = 16;
   const GLint mAtlasRows = 16;
};

typedef std::shared_ptr<Font> pFont;
typedef std::unique_ptr<Font> puFont;

}


int generateFontMetadata (const char* ttfFilePath,
                          const char* outputPNG,
                          const char* outputMETADATA);

//Font getFont (const char* ttfFilePath);

#endif /* FONT_GENERATOR_H_ */
