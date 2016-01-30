/*
 * LightManager.cpp
 *
 *  Created on: 18 Apr 2013
 *      Author: Filip Wasil
 */

#include <fillwave/management/LightManager.h>
#include <fillwave/Log.h>
#include <fillwave/Fillwave.h>
#include <fillwave/common/Macros.h>

FLOGINIT("LightManager", FERROR | FFATAL)

namespace fillwave {
namespace framework {

const glm::mat4 FILLWAVE_UV_BIAS_MATRIX(0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0,
		0.0, 0.0, 0.0, 0.5, 0.0, 0.5, 0.5, 0.5, 1.0);

LightManager::LightManager() {
	mLightBufferData.resize(
	FILLWAVE_MAX_SPOT_LIGHTS + FILLWAVE_MAX_DIRECTIONAL_LIGHTS);
}

pLightSpot LightManager::addLightSpot(
		pTexture2DRenderable shadowTexture,
		glm::vec3 position,
		glm::quat rotation,
		glm::vec4 color,
		pMoveable followed) {
	pLightSpot light;
	if (mSpotLights.size() < FILLWAVE_MAX_SPOT_LIGHTS) {
		light = pLightSpot(
				new LightSpot(shadowTexture, position, rotation, color,
						followed));

		FLOG_DEBUG("Added spot light ID : %lu", mSpotLights.size());

		mSpotLights.push_back(light);
	} else {
		light = pLightSpot();
		FLOG_ERROR(
				"Can not add more lights due to temporary engine limitation. Please contact fillwave@gmail.com for more info.");
	}
	return light;
}

pLightPoint LightManager::addLightPoint(
		pTexture3DRenderable shadowTexture,
		glm::vec3 position,
		glm::vec4 intensity,
		pMoveable followed) {
	pLightPoint light;
	FLOG_DEBUG("Going to add point light ID : %lu", mPointLights.size());
	if (mPointLights.size() < FILLWAVE_MAX_SPOT_LIGHTS) {
		light = pLightPoint(
				new LightPoint(shadowTexture, position, intensity, followed));
		FLOG_DEBUG("Added point light ID : %lu", mPointLights.size());
		mPointLights.push_back(light);
	} else {
		light = pLightPoint();
		FLOG_ERROR(
				"Can not add more lights due to temporary engine limitation. Please contact fillwave@gmail.com for more info.");
	}
	return light;
}

pLightDirectional LightManager::addLightDirectional(
		pTexture2DRenderable shadowTexture,
		glm::vec3 position,
		glm::quat rotation,
		glm::vec4 color,
		pMoveable followed) {
	pLightDirectional light = pLightDirectional();
	FLOG_DEBUG("Going to add directional light ID : %lu",
			mDirectionalLights.size());
	if (mDirectionalLights.size() < FILLWAVE_MAX_DIRECTIONAL_LIGHTS) {
		light = pLightDirectional(
				new LightDirectional(shadowTexture, position, rotation,
						color, followed));
		FLOG_DEBUG("Added directional light ID : %lu", mDirectionalLights.size());
		mDirectionalLights.push_back(light);
	} else {
		FLOG_ERROR(
				"Can not add more lights due to temporary engine limitation. Please contact fillwave@gmail.com for more info.");
	}
	return light;
}

void LightManager::removeLight(pLightSpot light) {
	remove(mSpotLights, light);
}

void LightManager::removeLight(pLightDirectional light) {
	remove(mDirectionalLights, light);
}

void LightManager::removeLight(pLightPoint light) {
	remove(mPointLights, light);
}

void LightManager::removeLights() {
	mSpotLights.clear();
	mDirectionalLights.clear();
	mPointLights.clear();
}

/*
 * Update each light translation according to its Entity
 */

void LightManager::updateLightEntities() {
	for (auto& it : mSpotLights) {
		it->updateFromFollowed();
		it->updateShadowCamera();
	}
	for (auto& it : mDirectionalLights) {
		it->updateFromFollowed();
		it->updateShadowCamera();
	}
	for (auto& it : mPointLights) {
		it->updateFromFollowed();
		it->updateShadowCamera();
	}
}

GLint LightManager::getLightsSpotHowMany() {
	return mSpotLights.size();
}

GLint LightManager::getLightsDirectionalHowMany() {
	return mDirectionalLights.size();
}

GLint LightManager::getLightsPointHowMany() {
	return mPointLights.size();
}

GLboolean LightManager::isLightsRefresh() {
	if (isMoveablesRefresh(mSpotLights)
			|| isMoveablesRefresh(mDirectionalLights)
			|| isMoveablesRefresh(mPointLights)) {
		return GL_TRUE;
	}
	return GL_FALSE;
}

void LightManager::resetLightsRefresh() {
	resetMoveablesRefresh(mSpotLights);
	resetMoveablesRefresh(mDirectionalLights);
	resetMoveablesRefresh(mPointLights);
}

pLightSpot LightManager::getLightSpot(GLint i) {
	return mSpotLights[i];
}

pLightPoint LightManager::getLightPoint(GLint i) {
	return mPointLights[i];
}

pLightDirectional LightManager::getLightDirectional(GLint i) {
	return mDirectionalLights[i];
}

void LightManager::pushLightUniforms(core::Program* program) {

	/* KEEP THIS ORDER !!! SPOT -> DIRECTIONAL -> POINT*/

	program->uniformPush("uNumberOfSpotLights",
			static_cast<GLint>(mSpotLights.size() + mDirectionalLights.size()));

#if defined(FILLWAVE_COMPILATION_DRIVER_WORKAROUNDS) && defined(FILLWAVE_COMPILATION_PC_GLES)
	/* Mesa shader compiler optimizes out "uNumberOfPointLights" but it should not */
	/* This causes a false positive error indication here */
#else
	program->uniformPush("uNumberOfPointLights",
			static_cast<GLint>(mPointLights.size()));
#endif /* defined(FILLWAVE_THIRD_PARTY_WORKAROUNDS) && defined(FILLWAVE_COMPILATION_PC_GLES) */

	GLint UBOIterator = 0;

	/* Spot lights */

	for (size_t i = 0; i < mSpotLights.size(); i++) {

		CameraPerspective camera =
				*(mSpotLights[i]->getShadowCamera().get());

		for (GLuint j = 0; j < 3; j++) {
			mLightBufferData[UBOIterator].position[j] = glm::value_ptr(
					mSpotLights[i]->getTranslation())[j];
		}
		mLightBufferData[UBOIterator].position[3] = 1.0;

		for (GLuint j = 0; j < 4; j++) {
			mLightBufferData[UBOIterator].intensity[j] = glm::value_ptr(
					mSpotLights[i]->getIntensity())[j];
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

	for (size_t i = 0; i < mDirectionalLights.size(); i++) {
		CameraOrthographic camera =
				*(mDirectionalLights[i]->getShadowCamera().get());

		for (GLuint j = 0; j < 3; j++) {
			mLightBufferData[UBOIterator].position[j] = glm::value_ptr(
					mDirectionalLights[i]->getTranslation())[j];
		}
		mLightBufferData[UBOIterator].position[3] = 1.0;

		for (GLuint j = 0; j < 4; j++) {
			mLightBufferData[UBOIterator].intensity[j] = glm::value_ptr(
					mDirectionalLights[i]->getIntensity())[j];
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

	for (size_t i = 0; i < mPointLights.size(); i++) {
		/*LightPoint* l = mPointLights[i].get();*/
		program->uniformPush(
				getStructField("uPointLights", "position", i),
				glm::vec4(mPointLights[i]->getTranslation(), 1.0));
		program->uniformPush(
				getStructField("uPointLights", "intensity", i),
				mPointLights[i]->getIntensity());
		program->uniformPush(getNotIndexableName("uPointShadowMap", i),
		FILLWAVE_SHADOW_FIRST_UNIT + UBOIterator);
		UBOIterator++;
	}

	if (isLightsRefresh()) {
		pushLightUniformBuffers(program);
		resetLightsRefresh();
	}
}

void LightManager::pushLightUniformsDR() {

	/* KEEP THIS ORDER !!! SPOT -> DIRECTIONAL -> POINT*/

	GLint UBOIterator = 0;

	/* Spot lights */
	for (size_t i = 0; i < mSpotLights.size(); i++) {

		CameraPerspective camera =
				*(mSpotLights[i]->getShadowCamera().get());

		for (GLuint j = 0; j < 3; j++) {
			mLightBufferData[UBOIterator].position[j] = glm::value_ptr(
					mSpotLights[i]->getTranslation())[j];
		}
		mLightBufferData[UBOIterator].position[3] = 1.0;

		for (GLuint j = 0; j < 4; j++) {
			mLightBufferData[UBOIterator].intensity[j] = glm::value_ptr(
					mSpotLights[i]->getIntensity())[j];
		}

		glm::mat4 matrix = FILLWAVE_UV_BIAS_MATRIX * camera.getViewProjection();
		for (GLuint j = 0; j < 16; j++) {
			mLightBufferData[UBOIterator].mvp[j] = glm::value_ptr(matrix)[j];
		}
		UBOIterator++;
	}

	/* Directional lights */
	for (size_t i = 0; i < mDirectionalLights.size(); i++) {
		CameraOrthographic camera =
				*(mDirectionalLights[i]->getShadowCamera().get());

		for (GLuint j = 0; j < 3; j++) {
			mLightBufferData[UBOIterator].position[j] = glm::value_ptr(
					mDirectionalLights[i]->getTranslation())[j];
		}
		mLightBufferData[UBOIterator].position[3] = 1.0;

		for (GLuint j = 0; j < 4; j++) {
			mLightBufferData[UBOIterator].intensity[j] = glm::value_ptr(
					mDirectionalLights[i]->getIntensity())[j];
		}

		glm::mat4 matrix = FILLWAVE_UV_BIAS_MATRIX * camera.getViewProjection();
		for (GLuint j = 0; j < 16; j++) {
			mLightBufferData[UBOIterator].mvp[j] = glm::value_ptr(matrix)[j];
		}
		UBOIterator++;
	}
}

void LightManager::updateDeferredBufferSpot(
		GLuint lightID,
		core::Program* program,
		GLint currentShadowUnit) {
	program->use();
	glm::vec3 translation = mSpotLights[lightID]->getTranslation();

	program->uniformPush("uLight.base.color",
			mSpotLights[lightID]->getIntensity().xyz());
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

void LightManager::updateDeferredBufferDirectional(
		GLuint lightID,
		core::Program* program,
		GLint /*currentShadowUnit*/) {
	program->use();
	glm::vec4 translation = glm::vec4(
			mDirectionalLights[lightID]->getTranslation(), 1.0);

	program->uniformPush("uLight.base.color",
			mDirectionalLights[lightID]->getIntensity().xyz());
	program->uniformPush("uLight.base.ambientIntensity", 0.15f);
	program->uniformPush("uLight.base.diffuseIntensity", 0.85f);
	program->uniformPush("uLight.direction", -translation.xyz());
	program->uniformPush("uSpecularPower", 255.0f);
}

void LightManager::updateDeferredBufferPoint(
		GLuint lightID,
		core::Program* program,
		GLint /*currentShadowUnit*/) {
	program->use();

	program->uniformPush("uLight.base.color",
			mPointLights[lightID]->getIntensity().xyz());
	program->uniformPush("uLight.base.ambientIntensity", 0.15f);
	program->uniformPush("uLight.base.diffuseIntensity", 0.85f);
	program->uniformPush("uLight.attenuation.constant", 0.4f);
	program->uniformPush("uLight.attenuation.linear", 0.3f);
	program->uniformPush("uLight.attenuation.exp", 0.1f);
	program->uniformPush("uSpecularPower", 255.0f);
}

void LightManager::pushLightUniformBuffers(core::Program* program) {
	program->uniformBlockPush(
	FILLWAVE_LIGHTS_BINDING_POINT_NAME, reinterpret_cast<GLfloat*>(mLightBufferData.data()));
}

void LightManager::bindShadowmaps() {
	GLint currentTextureUnit = FILLWAVE_SHADOW_FIRST_UNIT;
	for (size_t i = 0; i < mSpotLights.size(); i++) {
		mSpotLights[i]->getShadowTexture()->bind(currentTextureUnit++);
	}
	for (size_t i = 0; i < mDirectionalLights.size(); i++) {
		mDirectionalLights[i]->getShadowTexture()->bind(currentTextureUnit++);
	}
	for (size_t i = 0; i < mPointLights.size(); i++) {
		mPointLights[i]->getShadowTexture()->bind(currentTextureUnit++);
	}
}

GLfloat LightManager::computePointLightBoundingSphere(pLightPoint& light) {
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
