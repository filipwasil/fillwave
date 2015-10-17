/*
 * Moveable.cpp
 *
 *  Created on: Jun 2, 2014
 *      Author: filip
 */

#include <fillwave/models/Moveable.h>

namespace fillwave {
namespace models {

Moveable::Moveable(glm::vec3 translation, glm::quat rotation)
		:
				mTranslation(translation),
				mRotation(rotation),
				mScale(1.0),
				mRefresh(GL_TRUE) {

}

glm::vec3 Moveable::getTranslation() {
	return mTranslation;
}

void Moveable::moveTo(glm::vec3 coordinates) {
	mTranslation = coordinates;
	mRefresh = GL_TRUE;
}

void Moveable::moveToX(GLfloat distance) {
	mTranslation.x = distance;
	mRefresh = GL_TRUE;
}

void Moveable::moveToY(GLfloat distance) {
	mTranslation.y = distance;
	mRefresh = GL_TRUE;
}

void Moveable::moveToZ(GLfloat distance) {
	mTranslation.z = distance;
	mRefresh = GL_TRUE;
}

void Moveable::moveBy(glm::vec3 coordinates) {
	mTranslation += coordinates;
	mRefresh = GL_TRUE;
}

void Moveable::moveByX(GLfloat distance) {
	mTranslation.x += distance;
	mRefresh = GL_TRUE;
}

void Moveable::moveByY(GLfloat distance) {
	mTranslation.y += distance;
	mRefresh = GL_TRUE;
}

void Moveable::moveByZ(GLfloat distance) {
	mTranslation.z += distance;
	mRefresh = GL_TRUE;
}

void Moveable::moveInDirection(glm::vec3 direction) {
	mTranslation += glm::vec3(
			glm::mat4_cast(mRotation) * glm::vec4(direction, 1.0));
	mRefresh = GL_TRUE;
}

glm::vec3 Moveable::getScale() {
	return mScale;
}

void Moveable::scaleTo(GLfloat scale) {
	mScale = glm::vec3(scale, scale, scale);
	mRefresh = GL_TRUE;
}

void Moveable::scaleTo(glm::vec3 scale) {
	mScale = scale;
	mRefresh = GL_TRUE;
}

void Moveable::scaleToX(GLfloat scale) {
	mScale = glm::vec3(scale, mScale.y, mScale.z);
	mRefresh = GL_TRUE;
}

void Moveable::scaleToY(GLfloat scale) {
	mScale = glm::vec3(mScale.x, scale, mScale.z);
	mRefresh = GL_TRUE;
}

void Moveable::scaleToZ(GLfloat scale) {
	mScale = glm::vec3(scale, mScale.y, mScale.z);
	mRefresh = GL_TRUE;
}

glm::quat Moveable::getRotation() {
	return mRotation;
}

void Moveable::rotateTo(glm::quat rotation) {
	mRotation = rotation;
	mRefresh = GL_TRUE;
}

void Moveable::rotateTo(const glm::vec3 &axis, GLfloat angle) {
	glm::quat rotation = glm::angleAxis(angle, glm::normalize(axis));
	mRotation = rotation;
	mRefresh = GL_TRUE;
}

void Moveable::rotateByX(float angle) {
	rotateBy(glm::vec3(1.0, 0.0, 0.0), angle);
	mRefresh = GL_TRUE;
}

void Moveable::rotateByY(float angle) {
	rotateBy(glm::vec3(0.0, 1.0, 0.0), angle);
	mRefresh = GL_TRUE;
}

void Moveable::rotateByZ(float angle) {
	rotateBy(glm::vec3(0.0, 0.0, 1.0), angle);
	mRefresh = GL_TRUE;
}

void Moveable::rotateBy(const glm::vec3 &axis, GLfloat angle) {
	glm::vec3 Axis = glm::normalize(axis);
	Axis = (glm::mat4_cast(mRotation) * glm::vec4(Axis, 1.0)).xyz();

	Axis = Axis * sinf(angle / 2.0f);
	float scalar = cosf(angle / 2.0f);

	glm::quat offset(scalar, Axis.x, Axis.y, Axis.z);

	mRotation = offset * mRotation;
	mRotation = glm::normalize(mRotation);
	mRefresh = GL_TRUE;
}

void Moveable::updateMatrixCache() {
	mModelMatrixCache = glm::translate(glm::mat4(1.0), mTranslation)
			* glm::mat4_cast(mRotation) * glm::scale(glm::mat4(1.0), mScale);
}

GLboolean Moveable::isRefresh() {
	return mRefresh;
}

void Moveable::resetRefresh() {
	mRefresh = GL_FALSE;
}

} /* models */
} /* fillwave */
