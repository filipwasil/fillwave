/*
 * LightPoint.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: filip
 */

#include <fillwave/space/LightPoint.h>
#include <fillwave/common/Macros.h>
#include <fillwave/Log.h>

FLOGINIT("LightPoint", FERROR | FFATAL)

namespace fillwave {
namespace framework {

LightPoint::LightPoint(
   core::Texture3DRenderable* shadowTexture,
   glm::vec3 position,
   glm::vec4 intensity,
   Moveable* followed) :
	Light(position, intensity, followed),
	mShadowTexture(shadowTexture),
	mSphere(1.0, 10, 10) {
	mFaceCameras[GL_TEXTURE_CUBE_MAP_POSITIVE_X] = std::make_unique
	      < CameraPerspective
	      > (position, glm::normalize(
	            glm::angleAxis(glm::radians(90.0f),
	                           glm::normalize(glm::vec3(0.0, 1.0, 0.0)))
	            * glm::angleAxis(glm::radians(180.0f),
	                             glm::normalize(glm::vec3(1.0, 0.0, 0.0)))), glm::radians(
	            90.0), 1.0, //1440.0/900.0,
	         0.1, 1000.0), mFaceCameras[GL_TEXTURE_CUBE_MAP_NEGATIVE_X] =
	         std::make_unique < CameraPerspective
	         > (position, glm::normalize(
	               glm::angleAxis(glm::radians(-90.0f),
	                              glm::normalize(glm::vec3(0.0, 1.0, 0.0)))
	               * glm::angleAxis(glm::radians(180.0f),
	                                glm::normalize(glm::vec3(1.0, 0.0, 0.0)))), glm::radians(
	               90.0), 1.0, //1440.0/900.0,
	            0.1, 1000.0), mFaceCameras[GL_TEXTURE_CUBE_MAP_POSITIVE_Y] =
	            std::make_unique < CameraPerspective
	            > (position, glm::normalize(
	                  glm::angleAxis(glm::radians(90.0f),
	                                 glm::normalize(glm::vec3(1.0, 0.0, 0.0)))), glm::radians(
	                  90.0), 1.0, //1440.0/900.0,
	               0.1, 1000.0), mFaceCameras[GL_TEXTURE_CUBE_MAP_NEGATIVE_Y] =
	               std::make_unique < CameraPerspective
	               > (position, glm::normalize(
	                     glm::angleAxis(glm::radians(-90.0f),
	                                    glm::normalize(glm::vec3(1.0, 0.0, 0.0)))), glm::radians(
	                     90.0), 1.0, //1440.0/900.0,
	                  0.1, 1000.0), mFaceCameras[GL_TEXTURE_CUBE_MAP_POSITIVE_Z] =
	                  std::make_unique < CameraPerspective
	                  > (position, glm::normalize(
	                        glm::angleAxis(glm::radians(180.0f),
	                                       glm::normalize(glm::vec3(0.0, 0.0, 1.0)))), glm::radians(
	                        90.0), 1.0, //1440.0/900.0,
	                     0.1, 1000.0), mFaceCameras[GL_TEXTURE_CUBE_MAP_NEGATIVE_Z] =
	                     std::make_unique < CameraPerspective
	                     > (position, glm::normalize(
	                           glm::angleAxis(glm::radians(180.0f),
	                                 glm::normalize(glm::vec3(0.0, 1.0, 0.0)))
	                           * glm::angleAxis(glm::radians(180.0f),
	                                 glm::normalize(glm::vec3(0.0, 0.0, 1.0)))), glm::radians(
	                           90.0), 1.0, //1440.0/900.0,
	                        0.1, 1000.0);
}

core::Texture3DRenderable* LightPoint::getShadowTexture() {
	return mShadowTexture;
}

CameraPerspective* LightPoint::getShadowCamera(GLenum
      id) {
	if (mFaceCameras.count(id) == 1) {
		return mFaceCameras[id].get();
	} else {
		FLOG_FATAL(
		   "Can not get shadow camera. This should never happen. Good bye ...");
		return nullptr;
	}
}

void LightPoint::updateShadowCamera() {
	if (mFollowed) {
		mTranslation = mFollowed->getTranslation();
	}
	for (auto& it : mFaceCameras) {
		if (it.second->getTranslation() != mTranslation) {
			it.second->moveTo(mTranslation);
			it.second->update();
		}
	}
}

} /* framework */
} /* fillwave */
