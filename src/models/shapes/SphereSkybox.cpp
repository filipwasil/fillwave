/*
 * SphereSkybox.cpp
 *
 *  Created on: 18 May 2015
 *      Author: Filip Wasil
 */

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2015] Filip Wasil
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

#include <fillwave/models/shapes/SphereSkybox.h>
#include <fillwave/Fillwave.h>

namespace fillwave {
namespace models {

SphereSkybox::SphereSkybox(GLfloat radius,
        GLuint rings,
        GLuint sectors) {
   float const R = 1./(float)(rings-1);
   float const S = 1./(float)(sectors-1);
   int r, s;

   mVertices.resize(rings * sectors);

   auto vb = mVertices.begin();

   for(r = 0; r < rings; r++) {
      for(s = 0; s < sectors; s++) {
         float const y = sin( -M_PI_2 + M_PI * r * R );
         float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
         float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );

         (*vb).mPosition[0] = x * radius * mScale;
         (*vb).mPosition[1] = y * radius * mScale;
         (*vb).mPosition[2] = z * radius * mScale;
         (*vb).mPosition[3] = 1.0;

         vb++;
      }
   }

   mIndices.resize(rings * sectors * 6);
   auto i = mIndices.begin();
   for(r = 0; r < rings - 1; r++) {
      for(s = 0; s < sectors; s++) {
         if (r == rings - 1 || s == sectors - 1) {
            break;
         }

         *i++ = r * sectors + (s+1);
         *i++ = r * sectors + s;
         *i++ = (r+1) * sectors + (s+1);
         *i++ = (r+1) * sectors + s;
         *i++ = (r+1) * sectors + (s+1);
         *i++ = r * sectors + s;
      }
   }
}

SphereSkybox::~SphereSkybox() {

}

} /* models */
} /* fillwave */
