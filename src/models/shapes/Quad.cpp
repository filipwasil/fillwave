/*
 * Quad.cpp
 *
 *  Created on: May 25, 2015
 *      Author: filip
 */

#include <fillwave/models/shapes/Quad.h>

namespace fillwave {
namespace models {

Quad::Quad(GLfloat size) {

   mVertices.resize(6);

   core::VertexBasic position[6] = {
           { {-size,-size,0.0,1.0},{0.0,0.0,0.0,1.0},{0.0,0.0,-1.0},{1.0,0.0,0.0},{0.0,0.0},{0},{0.0} },
           { {size,-size,0.0,1.0},{0.0,0.0,0.0,1.0},{0.0,0.0,-1.0},{1.0,0.0,0.0},{1.0,0.0},{0},{0.0} },
           { {size,size,0.0,1.0},{0.0,0.0,0.0,1.0},{0.0,0.0,-1.0},{1.0,0.0,0.0},{1.0,1.0},{0},{0.0} },
           { {size,size,0.0,1.0},{0.0,0.0,0.0,1.0},{0.0,0.0,-1.0},{1.0,0.0,0.0},{1.0,1.0},{0},{0.0} },
           { {-size,size,0.0,1.0},{0.0,0.0,0.0,1.0},{0.0,0.0,-1.0},{1.0,0.0,0.0},{0.0,1.0},{0},{0.0} },
           { {-size,-size,0.0,1.0},{0.0,0.0,0.0,1.0},{0.0,0.0,-1.0},{1.0,0.0,0.0},{0.0,0.0},{0},{0.0} },
   };

   for (int i = 0; i < mVertices.size(); i++) {
      mVertices[i] = position[i];
      mIndices.push_back(i);
   }
}

Quad::~Quad() {

}

} /* models */
} /* fillwave */
