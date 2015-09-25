/*
 * Sphere.cpp
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

#include <fillwave/models/shapes/Sphere.h>
#include <fillwave/Fillwave.h>

FLOGINIT("Sphere", FERROR | FFATAL)

namespace fillwave {
namespace models {

Sphere::Sphere(GLfloat radius,
               GLuint rings,
               GLuint sectors,
               glm::vec3 color) {
   float const R = 1./(float)(rings-1);
   float const S = 1./(float)(sectors-1);
   float r, s;

   mVertices.resize(rings * sectors);

   auto vb = mVertices.begin();

   for(r = 0; r < rings; r++) {
      for(s = 0; s < sectors; s++) {
         float const y = sin( -M_PI_2 + M_PI * r * R );
         float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
         float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );

         (*vb).mTextureUV[0] = s*S;
         (*vb).mTextureUV[1] = r*R;

         (*vb).mPosition[0] = x * radius;
         (*vb).mPosition[1] = y * radius;
         (*vb).mPosition[2] = z * radius;
         (*vb).mPosition[3] = 1.0;

         (*vb).mNormal[0] = x;
         (*vb).mNormal[1] = y;
         (*vb).mNormal[2] = z;

         (*vb).mColor[0] = color.x;
         (*vb).mColor[1] = color.y;
         (*vb).mColor[2] = color.z;
         vb++;
      }
   }

   mIndices.resize((rings - 1) * sectors * 6 - 1);
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

Sphere::~Sphere() {

}

} /* models */
} /* fillwave */
