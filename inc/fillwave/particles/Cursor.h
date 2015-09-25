/*
 * Cursor.h
 *
 *  Created on: Nov 6, 2014
 *      Author: Filip Wasil
 */

#ifndef CURSOR_H_
#define CURSOR_H_

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

#include <fillwave/particles/Impostor.h>

namespace fillwave {
class Engine;
namespace particles {

/*! \class Cursor
 *
 * \brief Impostor to handle custom cursor instead of the standard one.
 *
 */

class Cursor: public Impostor {
public:
   Cursor(Engine* engine,
          pTexture texture);

   virtual ~Cursor();

   void move(glm::vec2 position);

   void draw();

private:
   GLfloat mScreenFactor;

   GLint mULCPosition,
   mULCScreenFactor,
   mULCTextureUnit,
   mULCSize;

   void initUniformsCache();
};

} /* particles */
typedef std::shared_ptr<particles::Cursor> pCursor;

static pCursor buildCursor(Engine* engine,
                           pTexture texture) {
   return pCursor(new particles::Cursor (engine, texture));
}

} /* fillwave */

#endif /* CURSOR_H_ */
