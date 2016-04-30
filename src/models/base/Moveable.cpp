/*
 * Moveable.cpp
 *
 *  Created on: Jun 2, 2014
 *      Author: filip
 */

#include <fillwave/models/base/Moveable.h>

namespace fillwave {
namespace framework {

Moveable::Moveable(glm::vec3 translation, glm::quat rotation) :
	mTranslation(translation),
	mRotation(rotation),
	mScale(1.0),
	mRefresh(true) {
}

glm::vec3 Moveable::getTranslation() {
	return mTranslation;
}

void Moveable::moveTo(glm::vec3 coordinates) {
	mTranslation = coordinates;
	mRefresh = true;
}

void Moveable::moveToX(GLfloat distance) {
	mTranslation.x = distance;
	mRefresh = true;
}

void Moveable::moveToY(GLfloat distance) {
	mTranslation.y = distance;
	mRefresh = true;
}

void Moveable::moveToZ(GLfloat distance) {
	mTranslation.z = distance;
	mRefresh = true;
}

void Moveable::moveBy(glm::vec3 coordinates) {
	mTranslation += coordinates;
	mRefresh = true;
}

void Moveable::moveByX(GLfloat distance) {
	mTranslation.x += distance;
	mRefresh = true;
}

void Moveable::moveByY(GLfloat distance) {
	mTranslation.y += distance;
	mRefresh = true;
}

void Moveable::moveByZ(GLfloat distance) {
	mTranslation.z += distance;
	mRefresh = true;
}

void Moveable::moveInDirection(glm::vec3 direction) {
	mTranslation += glm::vec3(
	                   glm::mat4_cast(mRotation) * glm::vec4(direction, 1.0));
	mRefresh = true;
}

glm::vec3 Moveable::getScale() {
	return mScale;
}

void Moveable::scaleTo(GLfloat scale) {
	mScale = glm::vec3(scale, scale, scale);
	mRefresh = true;
}

void Moveable::scaleTo(glm::vec3 scale) {
	mScale = scale;
	mRefresh = true;
}

void Moveable::scaleToX(GLfloat scale) {
	mScale = glm::vec3(scale, mScale.y, mScale.z);
	mRefresh = true;
}

void Moveable::scaleToY(GLfloat scale) {
	mScale = glm::vec3(mScale.x, scale, mScale.z);
	mRefresh = true;
}

void Moveable::scaleToZ(GLfloat scale) {
	mScale = glm::vec3(scale, mScale.y, mScale.z);
	mRefresh = true;
}

glm::quat Moveable::getRotation() {
	return mRotation;
}

void Moveable::rotateTo(glm::quat rotation) {
	mRotation = rotation;
	mRefresh = true;
}

void Moveable::rotateTo(const glm::vec3 &axis, GLfloat angle) {
	glm::quat rotation = glm::angleAxis(angle, glm::normalize(axis));
	mRotation = rotation;
	mRefresh = true;
}

void Moveable::rotateByX(float angle) {
	rotateBy(glm::vec3(1.0, 0.0, 0.0), angle);
	mRefresh = true;
}

void Moveable::rotateByY(float angle) {
	rotateBy(glm::vec3(0.0, 1.0, 0.0), angle);
	mRefresh = true;
}

void Moveable::rotateByZ(float angle) {
	rotateBy(glm::vec3(0.0, 0.0, 1.0), angle);
	mRefresh = true;
}

void Moveable::rotateBy(const glm::vec3 &axis, GLfloat angle) {
	glm::vec3 Axis = glm::normalize(axis);
	Axis = (glm::mat4_cast(mRotation) * glm::vec4(Axis, 1.0)).xyz();

	Axis = Axis * sinf(angle / 2.0f);
	float scalar = cosf(angle / 2.0f);

	glm::quat offset(scalar, Axis.x, Axis.y, Axis.z);

	mRotation = offset * mRotation;
	mRotation = glm::normalize(mRotation);
	mRefresh = true;
}

void Moveable::updateMatrixCache() {
	mMMC = glm::translate(glm::mat4(1.0), mTranslation)
	       * glm::mat4_cast(mRotation) * glm::scale(glm::mat4(1.0), mScale);
}

bool Moveable::isRefresh() {
	return mRefresh;
}

void Moveable::setRefresh(bool state) {
	mRefresh = state;
}

glm::mat4 Moveable::getParentMMC() {
	return mParentMMC;
}

glm::quat Moveable::getParentRotation() {
	return mParentRotation;
}

} /* framework */
} /* fillwave */
