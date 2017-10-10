#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <fillwave/models/base/Moveable.h>

namespace flw {
namespace flf {

TEST (Moveable, OneWaitOneStepByMoreThanWholeTime) {
	Moveable sut;
	sut.waitInTime(1.1f);
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
}

TEST (Moveable, TwoWaitsLessThanWholeTime) {
	Moveable sut;
	sut.waitInTime(1.1f);
	sut.waitInTime(1.1f);
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
}

TEST (Moveable, TwoWaitsMoreThanWholeTime) {
	Moveable sut;
	sut.waitInTime(1.1f);
	sut.waitInTime(1.1f);
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
	EXPECT_LE(0.8f - sut.stepInTime(1.0f), 0.0000001);
}

TEST (Moveable, TwoWaitsMoreThanWholeTimeSmallSteps) {
	Moveable sut;
	sut.waitInTime(1.1f);
	sut.waitInTime(1.1f);
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.55f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.1f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_LE(0.1f - sut.stepInTime(0.2f), 0.0000001);
}

TEST (Moveable, OneMoveOneStepByMoreThanWholeTime) {
	Moveable sut;
	sut.moveBy(1.1f, glm::vec3(0.1, 0.1, 0.2));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
}

TEST (Moveable, TwoMovesLessThanWholeTime) {
	Moveable sut;
	sut.moveBy(1.1f, glm::vec3(0.1, 0.1, 0.2));
	sut.moveBy(1.1f, glm::vec3(0.1, 0.1, 0.2));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
}

TEST (Moveable, TwoMovesMoreThanWholeTime) {
	Moveable sut;
	sut.moveBy(1.1f, glm::vec3(0.1, 0.1, 0.2));
	sut.moveBy(1.1f, glm::vec3(0.1, 0.1, 0.2));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
	EXPECT_LE(0.8f - sut.stepInTime(1.0f), 0.0000001);
}

TEST (Moveable, TwoMovesMoreThanWholeTimeSmallSteps) {
	Moveable sut;
	sut.moveBy(1.1f, glm::vec3(0.1, 0.1, 0.2));
	sut.moveBy(1.1f, glm::vec3(0.1, 0.1, 0.2));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.55f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.1f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_LE(0.1f - sut.stepInTime(0.2f), 0.0000001);
}

TEST (Moveable, OneScaleOneStepByMoreThanWholeTime) {
	Moveable sut;
	sut.scaleBy(1.1f, glm::vec3(0.1, 0.1, 0.2));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
}

TEST (Moveable, TwoScalesLessThanWholeTime) {
	Moveable sut;
	sut.scaleBy(1.1f, glm::vec3(0.1, 0.1, 0.2));
	sut.scaleBy(1.1f, glm::vec3(0.1, 0.1, 0.2));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
}

TEST (Moveable, TwoScaleMoreThanWholeTime) {
	Moveable sut;
	sut.scaleBy(1.1f, glm::vec3(0.1, 0.1, 0.2));
	sut.scaleBy(1.1f, glm::vec3(0.1, 0.1, 0.2));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
	EXPECT_LE(0.8f - sut.stepInTime(1.0f), 0.0000001);
}

TEST (Moveable, TwoScaleMoreThanWholeTimeSmallSteps) {
	Moveable sut;
	sut.scaleBy(1.1f, glm::vec3(0.1, 0.1, 0.2));
	sut.scaleBy(1.1f, glm::vec3(0.1, 0.1, 0.2));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.55f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.1f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_LE(0.1f - sut.stepInTime(0.2f), 0.0000001);
}

TEST (Moveable, OneRotateOneStepByMoreThanWholeTime) {
	Moveable sut;
	sut.rotateBy(1.1f, 1.0f, glm::vec3(0.1, 0.2, 0.4));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
}

TEST (Moveable, TwoRotateLessThanWholeTime) {
	Moveable sut;
	sut.rotateBy(1.1f, 1.0f, glm::vec3(0.1, 0.2, 0.4));
	sut.rotateBy(1.1f, 1.0f, glm::vec3(0.1, 0.2, 0.4));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
}

TEST (Moveable, TwoRotateMoreThanWholeTime) {
	Moveable sut;
	sut.rotateBy(1.1f, 1.0f, glm::vec3(0.1, 0.2, 0.4));
	sut.rotateBy(1.1f, 1.0f, glm::vec3(0.1, 0.2, 0.4));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
	EXPECT_LE(0.8f - sut.stepInTime(1.0f), 0.0000001);
}

TEST (Moveable, TwoRotateMoreThanWholeTimeSmallSteps) {
	Moveable sut;
	sut.rotateBy(1.1f, 1.0f, glm::vec3(0.1, 0.2, 0.4));
	sut.rotateBy(1.1f, 1.0f, glm::vec3(0.1, 0.2, 0.4));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.55f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.1f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_LE(0.1f - sut.stepInTime(0.2f), 0.0000001);
}

TEST (Moveable, RotateByTheSameRotation) {
	Moveable sut;
	sut.rotateBy(1.1f, 0.0f, glm::vec3(1.0, 0.0, 0.0));
	sut.stepInTime(1.0f);
	EXPECT_EQ(glm::quat(1.0, 0.0, 0.0, 0.0), sut.getRotation());
}

TEST (Moveable, RotateByDifferentRotation) {
	Moveable sut;
	sut.rotateBy(1.1f, 1.0f, glm::vec3(1.0, 0.0, 0.0));
	sut.stepInTime(1.0f);
	EXPECT_NE(glm::quat(1.0, 0.0, 0.0, 0.0), sut.getRotation());
}

TEST (Moveable, RotateByDifferentRotationCheckResultAfterFullStep) {
	Moveable sut1, sut2;
	sut2.rotateTo(glm::vec3(1.0, 0.0, 0.0), 1.0f);
	sut1.rotateBy(1.1f, 1.0f, glm::vec3(1.0, 0.0, 0.0));
	sut1.stepInTime(1.1f);
	EXPECT_EQ(sut2.getRotation(), sut1.getRotation());
}

TEST (Moveable, RotateByDifferentRotationCheckResultAfterHalfStep) {
	Moveable sut1, sut2;
	sut2.rotateTo(glm::vec3(1.0, 0.0, 0.0), 0.5f);
	sut1.rotateBy(1.1f, 1.0f, glm::vec3(1.0, 0.0, 0.0));
	sut1.stepInTime(0.55f);
	EXPECT_EQ(sut2.getRotation(), sut1.getRotation());
}

TEST (Moveable, RotateByDifferentRotationCheckResultAfterOneAndHalfStep) {
	Moveable sut1, sut2;
	sut2.rotateTo(glm::vec3(1.0, 0.0, 0.0), 1.5f);
	sut1.rotateBy(1.1f, 1.0f, glm::vec3(1.0, 0.0, 0.0));
	sut1.rotateBy(1.1f, 1.0f, glm::vec3(1.0, 0.0, 0.0));
	sut1.stepInTime(1.1f);
	sut1.stepInTime(0.55f);
	EXPECT_EQ(sut2.getRotation(), sut1.getRotation());
}

TEST (Moveable, MoveByTheSamePosition) {
	Moveable sut;
	sut.moveBy(1.1f, glm::vec3(0.0, 0.0, 0.0));
	sut.stepInTime(1.0f);
	EXPECT_EQ(glm::vec3(0.0, 0.0, 0.0), sut.getTranslation());
}

TEST (Moveable, MoveByDifferentPosition) {
	Moveable sut;
	sut.moveBy(1.1f, glm::vec3(1.0, 2.0, 3.0));
	sut.stepInTime(1.0f);
	EXPECT_NE(glm::vec3(1.0, 0.0, 0.0), sut.getTranslation());
}

TEST (Moveable, MoveByDifferentPositionCheckResultAfterFullStep) {
	Moveable sut1, sut2;
	sut2.moveTo(glm::vec3(1.0, 5.0, 10.0));
	sut1.moveBy(1.1f, glm::vec3(1.0, 5.0, 10.0));
	sut1.stepInTime(1.1f);
	EXPECT_EQ(sut2.getTranslation(), sut1.getTranslation());
}

TEST (Moveable, MoveByDifferentPositionCheckResultAfterHalfStep) {
	Moveable sut1, sut2;
	sut2.moveTo(glm::vec3(0.5, 1.0, 2.0));
	sut1.moveBy(1.1f, glm::vec3(1.0, 2.0, 4.0));
	sut1.stepInTime(0.55f);
	EXPECT_EQ(sut2.getTranslation(), sut1.getTranslation());
}

TEST (Moveable, MoveByDifferentPositionCheckResultAfterOneAndHalfStep) {
	Moveable sut1, sut2;
	sut2.moveTo(glm::vec3(1.5, 3.0, 9.0));
	sut1.moveBy(1.1f, glm::vec3(1.0, 2.0, 6.0));
	sut1.moveBy(1.1f, glm::vec3(1.0, 2.0, 6.0));
	sut1.stepInTime(1.1f);
	sut1.stepInTime(0.55f);
	EXPECT_EQ(sut2.getTranslation(), sut1.getTranslation());
}

TEST (Moveable, ScaleByTheSamePosition) {
	Moveable sut;
	sut.scaleBy(1.1f, glm::vec3(0.0, 0.0, 0.0));
	sut.stepInTime(1.0f);
	EXPECT_EQ(glm::vec3(1.0, 1.0, 1.0), sut.getScale());
}

TEST (Moveable, ScaleByDifferentPosition) {
	Moveable sut;
	sut.scaleBy(1.1f, glm::vec3(1.0, 2.0, 3.0));
	sut.stepInTime(1.0f);
	EXPECT_NE(glm::vec3(1.0, 0.0, 0.0), sut.getScale());
}

TEST (Moveable, ScaleByDifferentScaleCheckResultAfterFullStep) {
	Moveable sut1, sut2;
	sut2.scaleTo(glm::vec3(2.0, 6.0, 11.0));
	sut1.scaleBy(1.1f, glm::vec3(1.0, 5.0, 10.0));
	sut1.stepInTime(1.1f);
	EXPECT_EQ(sut2.getScale(), sut1.getScale());
}

TEST (Moveable, ScaleByDifferentScaleCheckResultAfterHalfStep) {
	Moveable sut1, sut2;
	sut2.scaleTo(glm::vec3(0.5, 1.0, 1.5));
	sut1.scaleBy(1.1f, glm::vec3(-1.0, 0.0, 1.0));
	sut1.stepInTime(0.55f);
	EXPECT_EQ(sut2.getScale(), sut1.getScale());
}

TEST (Moveable, ScaleByDifferentScaleCheckResultAfterOneAndHalfStep) {
	Moveable sut1, sut2;
	sut2.scaleTo(glm::vec3(2.5, 4.0, 10.0));
	sut1.scaleBy(1.1f, glm::vec3(1.0, 2.0, 6.0));
	sut1.scaleBy(1.1f, glm::vec3(1.0, 2.0, 6.0));
	sut1.stepInTime(1.1f);
	sut1.stepInTime(0.55f);
	EXPECT_EQ(sut2.getScale(), sut1.getScale());
}

TEST (Moveable, stop) {
	Moveable sut1, sut2;
	sut2.scaleTo(glm::vec3(2.5, 4.0, 10.0));
	sut1.scaleBy(1.1f, glm::vec3(1.0, 2.0, 6.0));
	sut1.scaleBy(1.1f, glm::vec3(1.0, 2.0, 6.0));
	sut1.stepInTime(1.1f);
	sut1.stepInTime(0.55f);
	sut1.stop();
	sut1.stepInTime(1.1f);
	sut1.stepInTime(0.55f);
	sut1.stepInTime(1.1f);
	sut1.stepInTime(0.55f);
	sut1.stepInTime(1.1f);
	sut1.stepInTime(0.55f);
	sut1.stepInTime(1.1f);
	sut1.stepInTime(0.55f);
	EXPECT_EQ(sut2.getScale(), sut1.getScale());
}

} /* flf */
} /* flw */
