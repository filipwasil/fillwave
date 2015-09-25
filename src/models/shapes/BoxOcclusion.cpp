/*
 * BoxOcclusion.cpp
 *
 *  Created on: 10 Jun 2015
 *      Author: Filip Wasil
 */

#include <fillwave/models/shapes/BoxOcclusion.h>
#include <glm/gtx/rotate_vector.hpp>

FLOGINIT("BoxOcclusion", FERROR | FFATAL)

namespace fillwave {
namespace models {

BoxOcclusion::BoxOcclusion(GLfloat quadSize):mSize(quadSize),
                                             mQuad(quadSize) {
   std::vector<core::VertexBasic> quadVertices = mQuad.getVertices();
   std::vector<glm::vec3> vertVertices;

   mVertices.resize(36);

   /* Back */
   for (int i = 0; i < 6; i++) {
      vertVertices.push_back(
            glm::vec3(quadVertices[i].mPosition[0],
                  quadVertices[i].mPosition[1],
                  quadVertices[i].mPosition[2] += mSize));
   }

   /* Down */
   for (GLuint i = 0; i < 6; i++) {
      glm::vec3 vec(glm::rotateX(vertVertices[i], glm::radians(90.0f)));
      vertVertices.push_back(vec);
   }

   /* Back */
   for (GLuint i = 0; i < 6; i++) {
      glm::vec3 vec(glm::rotateX(vertVertices[i], glm::radians(180.0f)));
      vertVertices.push_back(vec);
   }

   /* Up */
   for (GLuint i = 0; i < 6; i++) {
      glm::vec3 vec(glm::rotateX(vertVertices[i], glm::radians(270.0f)));
      vertVertices.push_back(vec);
   }

   /* Right */
   for (GLuint i = 0; i < 6; i++) {
      glm::vec3 vec = glm::rotateZ(
            glm::rotateX(vertVertices[i], glm::radians(90.0f)),
            glm::radians(90.0f));
      vertVertices.push_back(vec);
   }

   for (GLuint i = 0; i < 6; i++) {
      glm::vec3 vec = glm::rotateZ(
            glm::rotateX(vertVertices[i], glm::radians(90.0f)),
            glm::radians(-90.0f));
      vertVertices.push_back(vec);
   }

   /* Vertices and Indices */
   for (GLuint i = 0; i < vertVertices.size(); i++) {
      mVertices[i].mPosition[0] = vertVertices[i].x;
      mVertices[i].mPosition[1] = vertVertices[i].y;
      mVertices[i].mPosition[2] = vertVertices[i].z;
      mVertices[i].mPosition[3] = 1.0f;
      mIndices.push_back(i);
   }

//   for (GLuint i = 0; i < mVertices.size(); i++) {
//      FLOG_USER("%f %f %f",
//    		    mVertices[i].mPosition[0],
//    		    mVertices[i].mPosition[1],
//    		    mVertices[i].mPosition[2]);
//   }
}

BoxOcclusion::~BoxOcclusion() {

}

} /* models */
} /* fillwave */
