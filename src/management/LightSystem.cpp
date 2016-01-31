/*
 * LightSystem.cpp
 *
 *  Created on: 18 Apr 2013
 *      Author: Filip Wasil
 */

#include <fillwave/Log.h>
#include <fillwave/Fillwave.h>
#include <fillwave/common/Macros.h>
#include <fillwave/management/LightSystem.h>

FLOGINIT("LightSystem", FERROR | FFATAL)

namespace fillwave {
namespace framework {

const glm::mat4 FILLWAVE_UV_BIAS_MATRIX(0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0,
		0.0, 0.0, 0.0, 0.5, 0.0, 0.5, 0.5, 0.5, 1.0);

LightSystem::LightSystem() {
	mLightBufferData.resize(
	FILLWAVE_MAX_SPOT_LIGHTS + FILLWAVE_MAX_DIRECTIONAL_LIGHTS);
}

void LightSystem::clear() {
	mLightsSpot.clear();
	mLightsDirectional.clear();
	mLightsPoint.clear();
}

bool LightSystem::isLightsRefresh() {
	if (isMoveablesRefresh(mLightsSpot)
			|| isMoveablesRefresh(mLightsDirectional)
			|| isMoveablesRefresh(mLightsPoint)) {
		return true;
	}
	return false;
}

void LightSystem::resetLightsRefresh() {
	resetMoveablesRefresh(mLightsSpot);
	resetMoveablesRefresh(mLightsDirectional);
	resetMoveablesRefresh(mLightsPoint);
}

/*
 * Update each light translation according to its Entity
 */

void LightSystem::updateLightEntities() {
	for (auto& it : mLightsSpot) {
		it->updateFromFollowed();
		it->updateShadowCamera();
	}
	for (auto& it : mLightsDirectional) {
		it->updateFromFollowed();
		it->updateShadowCamera();
	}
	for (auto& it : mLightsPoint) {
		it->updateFromFollowed();
		it->updateShadowCamera();
	}
}

void LightSystem::pushLightUniforms(core::Program* program) {

	/* KEEP THIS ORDER !!! SPOT -> DIRECTIONAL -> POINT*/

	program->uniformPush("uNumberOfSpotLights",
			static_cast<GLint>(mLightsSpot.size() + mLightsDirectional.size()));

#if defined(FILLWAVE_COMPILATION_DRIVER_WORKAROUNDS) && defined(FILLWAVE_COMPILATION_PC_GLES)
	/* Mesa shader compiler optimizes out "uNumberOfPointLights" but it should not */
	/* This causes a false positive error indication here */
#else
	program->uniformPush("uNumberOfPointLights",
			static_cast<GLint>(mLightsSpot.size()));
#endif /* defined(FILLWAVE_THIRD_PARTY_WORKAROUNDS) && defined(FILLWAVE_COMPILATION_PC_GLES) */

	GLint UBOIterator = 0;

	/* Spot lights */

	for (size_t i = 0; i < mLightsSpot.size(); i++) {
		LightSpot* lightS = mLightsSpot[i].get();
		CameraPerspective camera =
				*(lightS->getShadowCamera().get());

		for (GLuint j = 0; j < 3; j++) {
			mLightBufferData[UBOIterator].position[j] = glm::value_ptr(
					lightS->getTranslation())[j];
		}
		mLightBufferData[UBOIterator].position[3] = 1.0;

		for (GLuint j = 0; j < 4; j++) {
			mLightBufferData[UBOIterator].intensity[j] = glm::value_ptr(
					lightS->getIntensity())[j];
		}

		glm::mat4 matrix = FILLWAVE_UV_BIAS_MATRIX * camera.getViewProjection();
		for (GLuint j = 0; j < 16; j++) {
			mLightBufferData[UBOIterator].mvp[j] = glm::value_ptr(matrix)[j];
		}

		program->uniformPush(
				getNotIndexableName("uShadowMap", UBOIterator),
				FILLWAVE_SHADOW_FIRST_UNIT + UBOIterator);
		UBOIterator++;
	}

	/* Directional lights */

	for (size_t i = 0; i < mLightsDirectional.size(); i++) {
		CameraOrthographic camera =
				*(mLightsDirectional[i]->getShadowCamera().get());

		for (GLuint j = 0; j < 3; j++) {
			mLightBufferData[UBOIterator].position[j] = glm::value_ptr(
					mLightsDirectional[i]->getTranslation())[j];
		}
		mLightBufferData[UBOIterator].position[3] = 1.0;

		for (GLuint j = 0; j < 4; j++) {
			mLightBufferData[UBOIterator].intensity[j] = glm::value_ptr(
					mLightsDirectional[i]->getIntensity())[j];
		}

		glm::mat4 matrix = FILLWAVE_UV_BIAS_MATRIX * camera.getViewProjection();
		for (GLuint j = 0; j < 16; j++) {
			mLightBufferData[UBOIterator].mvp[j] = glm::value_ptr(matrix)[j];
		}

		program->uniformPush(
				getNotIndexableName("uShadowMap", UBOIterator),
				FILLWAVE_SHADOW_FIRST_UNIT + UBOIterator);
		UBOIterator++;
	}

	/* Point lights */

	for (size_t i = 0; i < mLightsPoint.size(); i++) {
		/*LightPoint* l = mPointLights[i].get();*/
		program->uniformPush(
				getStructField("uPointLights", "position", i),
				glm::vec4(mLightsPoint[i]->getTranslation(), 1.0));
		program->uniformPush(
				getStructField("uPointLights", "intensity", i),
				mLightsPoint[i]->getIntensity());
		program->uniformPush(getNotIndexableName("uPointShadowMap", i),
		FILLWAVE_SHADOW_FIRST_UNIT + UBOIterator);
		UBOIterator++;
	}

	if (isLightsRefresh()) {
		pushLightUniformBuffers(program);
		resetLightsRefresh();
	}
}

void LightSystem::pushLightUniformsDR() {

	/* KEEP THIS ORDER !!! SPOT -> DIRECTIONAL -> POINT*/

	GLint UBOIterator = 0;

	/* Spot lights */
	for (size_t i = 0; i < mLightsSpot.size(); i++) {

		CameraPerspective camera =
				*(mLightsSpot[i]->getShadowCamera().get());

		for (GLuint j = 0; j < 3; j++) {
			mLightBufferData[UBOIterator].position[j] = glm::value_ptr(
					mLightsSpot[i]->getTranslation())[j];
		}
		mLightBufferData[UBOIterator].position[3] = 1.0;

		for (GLuint j = 0; j < 4; j++) {
			mLightBufferData[UBOIterator].intensity[j] = glm::value_ptr(
					mLightsSpot[i]->getIntensity())[j];
		}

		glm::mat4 matrix = FILLWAVE_UV_BIAS_MATRIX * camera.getViewProjection();
		for (GLuint j = 0; j < 16; j++) {
			mLightBufferData[UBOIterator].mvp[j] = glm::value_ptr(matrix)[j];
		}
		UBOIterator++;
	}

	/* Directional lights */
	for (size_t i = 0; i < mLightsDirectional.size(); i++) {
		CameraOrthographic camera =
				*(mLightsDirectional[i]->getShadowCamera().get());

		for (GLuint j = 0; j < 3; j++) {
			mLightBufferData[UBOIterator].position[j] = glm::value_ptr(
					mLightsDirectional[i]->getTranslation())[j];
		}
		mLightBufferData[UBOIterator].position[3] = 1.0;

		for (GLuint j = 0; j < 4; j++) {
			mLightBufferData[UBOIterator].intensity[j] = glm::value_ptr(
					mLightsDirectional[i]->getIntensity())[j];
		}

		glm::mat4 matrix = FILLWAVE_UV_BIAS_MATRIX * camera.getViewProjection();
		for (GLuint j = 0; j < 16; j++) {
			mLightBufferData[UBOIterator].mvp[j] = glm::value_ptr(matrix)[j];
		}
		UBOIterator++;
	}
}

void LightSystem::updateDeferredBufferSpot(
		GLuint lightID,
		core::Program* program,
		GLint currentShadowUnit) {
	program->use();
	glm::vec3 translation = mLightsSpot[lightID]->getTranslation();

	program->uniformPush("uLight.base.color",
			mLightsSpot[lightID]->getIntensity().xyz());
	program->uniformPush("uLight.base.ambientIntensity", 0.15f);
	program->uniformPush("uLight.base.diffuseIntensity", 0.85f);
	program->uniformPush("uLight.attenuation.constant", 0.1f);
	program->uniformPush("uLight.attenuation.linear", 0.4f);
	program->uniformPush("uLight.attenuation.exp", 0.1f);
	program->uniformPush("uLight.position", translation);
	program->uniformPush("uLight.mvp",
			glm::make_mat4(
					mLightBufferData[currentShadowUnit - FILLWAVE_SHADOW_FIRST_UNIT].mvp));

	program->uniformPush("uShadowMap", currentShadowUnit);
	program->uniformPush("uSpecularPower", 255.0f);
}

void LightSystem::updateDeferredBufferDirectional(
		GLuint lightID,
		core::Program* program,
		GLint /*currentShadowUnit*/) {
	program->use();
	glm::vec4 translation = glm::vec4(
			mLightsDirectional[lightID]->getTranslation(), 1.0);

	program->uniformPush("uLight.base.color",
			mLightsDirectional[lightID]->getIntensity().xyz());
	program->uniformPush("uLight.base.ambientIntensity", 0.15f);
	program->uniformPush("uLight.base.diffuseIntensity", 0.85f);
	program->uniformPush("uLight.direction", -translation.xyz());
	program->uniformPush("uSpecularPower", 255.0f);
}

void LightSystem::updateDeferredBufferPoint(
		GLuint lightID,
		core::Program* program,
		GLint /*currentShadowUnit*/) {
	program->use();

	program->uniformPush("uLight.base.color",
			mLightsPoint[lightID]->getIntensity().xyz());
	program->uniformPush("uLight.base.ambientIntensity", 0.15f);
	program->uniformPush("uLight.base.diffuseIntensity", 0.85f);
	program->uniformPush("uLight.attenuation.constant", 0.4f);
	program->uniformPush("uLight.attenuation.linear", 0.3f);
	program->uniformPush("uLight.attenuation.exp", 0.1f);
	program->uniformPush("uSpecularPower", 255.0f);
}

void LightSystem::pushLightUniformBuffers(core::Program* program) {
	program->uniformBlockPush(
	FILLWAVE_LIGHTS_BINDING_POINT_NAME, reinterpret_cast<GLfloat*>(mLightBufferData.data()));
}

void LightSystem::bindShadowmaps() {
	GLint currentTextureUnit = FILLWAVE_SHADOW_FIRST_UNIT;
	for (size_t i = 0; i < mLightsSpot.size(); i++) {
		mLightsSpot[i]->getShadowTexture()->bind(currentTextureUnit++);
	}
	for (size_t i = 0; i < mLightsDirectional.size(); i++) {
		mLightsDirectional[i]->getShadowTexture()->bind(currentTextureUnit++);
	}
	for (size_t i = 0; i < mLightsPoint.size(); i++) {
		mLightsPoint[i]->getShadowTexture()->bind(currentTextureUnit++);
	}
}

GLfloat LightSystem::computePointLightBoundingSphere(pLightPoint& light) {
	glm::vec4 intensity = light->getIntensity();
	LightAttenuationData attenuation = light->getAttenuation();
	GLfloat diffuseIntensity = 1.0;

	GLfloat MaxChannel = glm::max(glm::max(intensity.x, intensity.y),
			intensity.z);

	GLfloat ret = (-attenuation.mLinear
			+ glm::sqrt(
					attenuation.mLinear * attenuation.mLinear
							- 4 * attenuation.mExp
									* (attenuation.mExp
											- 256.0f * MaxChannel * diffuseIntensity))) / 2
			* attenuation.mExp;
	return ret;
}

} /* framework */
} /* fillwave */
