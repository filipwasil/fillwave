/*
 * LightManager.cpp
 *
 *  Created on: 18 Apr 2013
 *      Author: Filip Wasil
 */

#include <fillwave/management/LightManager.h>
#include <fillwave/extras/Log.h>
#include <fillwave/Fillwave.h>

FLOGINIT("LightManager", FERROR | FFATAL)

namespace fillwave {
namespace manager {

LightManager::LightManager(GLsizei screenWidth, GLsizei screenHeight)
		: mShadowWidth(screenWidth), mShadowHeight(screenHeight) {
	mLightBufferData.resize(
	FILLWAVE_MAX_SPOT_LIGHTS + FILLWAVE_MAX_DIRECTIONAL_LIGHTS);
}

pLightSpot LightManager::addLightSpot(
		pTexture2DRenderable shadowTexture,
		glm::vec3 position,
		glm::quat rotation,
		glm::vec4 color,
		pEntity entity) {
	pLightSpot light;
	if (mSpotLights.size() < FILLWAVE_MAX_SPOT_LIGHTS) {
		light = pLightSpot(
				new space::LightSpot(shadowTexture, position, rotation, color,
						entity));

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
		pEntity entity) {
	pLightPoint light;
	FLOG_DEBUG("Going to add point light ID : %lu", mPointLights.size());
	if (mPointLights.size() < FILLWAVE_MAX_SPOT_LIGHTS) {
		light = pLightPoint(
				new space::LightPoint(shadowTexture, position, intensity, entity));
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
		pEntity entity) {
	pLightDirectional light = pLightDirectional();
	FLOG_DEBUG("Going to add directional light ID : %lu",
			mDirectionalLights.size());
	if (mDirectionalLights.size() < FILLWAVE_MAX_DIRECTIONAL_LIGHTS) {
		light = pLightDirectional(
				new space::LightDirectional(shadowTexture, position, rotation,
						color, entity));
		FLOG_DEBUG("Added directional light ID : %lu", mDirectionalLights.size());
		mDirectionalLights.push_back(light);
	} else {
		FLOG_ERROR(
				"Can not add more lights due to temporary engine limitation. Please contact fillwave@gmail.com for more info.");
	}
	return light;
}

void LightManager::removeLight(pLightSpot light) {
	auto it = std::find(mSpotLights.begin(), mSpotLights.end(), light);
	if (it != mSpotLights.end()) {
		mSpotLights.erase(it);
	}
}

void LightManager::removeLight(pLightDirectional light) {
	auto it = std::find(mDirectionalLights.begin(), mDirectionalLights.end(),
			light);
	if (it != mDirectionalLights.end()) {
		mDirectionalLights.erase(it);
	}
}

void LightManager::removeLight(pLightPoint light) {
	auto it = std::find(mPointLights.begin(), mPointLights.end(), light);
	if (it != mPointLights.end()) {
		mPointLights.erase(it);
	}
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
	if (isRefreshLight(mSpotLights) || isRefreshLight(mDirectionalLights)
			|| isRefreshLight(mPointLights)) {
		return GL_TRUE;
	}
	return GL_FALSE;
}

void LightManager::resetLightsRefresh() {
	resetRefreshLight(mSpotLights);
	resetRefreshLight(mDirectionalLights);
	resetRefreshLight(mPointLights);
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
	program->uniformPush("uNumberOfPointLights",
			static_cast<GLint>(mPointLights.size()));

	GLint UBOIterator = 0;

	/* Spot lights */

	for (size_t i = 0; i < mSpotLights.size(); i++) {

		space::CameraPerspective camera =
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

		glm::mat4 matrix = mBiasMatrix * camera.getViewProjection();
		for (GLuint j = 0; j < 16; j++) {
			mLightBufferData[UBOIterator].mvp[j] = glm::value_ptr(matrix)[j];
		}

		program->uniformPush(
				strings::getNotIndexableName("uShadowMap", UBOIterator),
				FILLWAVE_SHADOW_FIRST_UNIT + UBOIterator);
		UBOIterator++;
	}

	/* Directional lights */

	for (size_t i = 0; i < mDirectionalLights.size(); i++) {
		space::CameraOrthographic camera =
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

		glm::mat4 matrix = mBiasMatrix * camera.getViewProjection();
		for (GLuint j = 0; j < 16; j++) {
			mLightBufferData[UBOIterator].mvp[j] = glm::value_ptr(matrix)[j];
		}

		program->uniformPush(
				strings::getNotIndexableName("uShadowMap", UBOIterator),
				FILLWAVE_SHADOW_FIRST_UNIT + UBOIterator);
		UBOIterator++;
	}

	/* Point lights */

	for (size_t i = 0; i < mPointLights.size(); i++) {
		/*space::LightPoint* l = mPointLights[i].get();*/
		program->uniformPush(
				strings::getStructField("uPointLights", "position", i),
				glm::vec4(mPointLights[i]->getTranslation(), 1.0));
		program->uniformPush(
				strings::getStructField("uPointLights", "intensity", i),
				mPointLights[i]->getIntensity());
		program->uniformPush(strings::getNotIndexableName("uPointShadowMap", i),
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

		space::CameraPerspective camera =
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

		glm::mat4 matrix = mBiasMatrix * camera.getViewProjection();
		for (GLuint j = 0; j < 16; j++) {
			mLightBufferData[UBOIterator].mvp[j] = glm::value_ptr(matrix)[j];
		}
		UBOIterator++;
	}

	/* Directional lights */
	for (size_t i = 0; i < mDirectionalLights.size(); i++) {
		space::CameraOrthographic camera =
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

		glm::mat4 matrix = mBiasMatrix * camera.getViewProjection();
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
	FILLWAVE_LIGHTS_BINDING_POINT_NAME, (GLfloat*) mLightBufferData.data());
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
	space::LightAttenuationData attenuation = light->getAttenuation();
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

} /* manager */
} /* fillwave */
