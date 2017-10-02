#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <fillwave/models/base/MoveableEased.h>

namespace flw {
namespace flf {

TEST (MoveableEased, OneWaitOneStepByMoreThanWholeTime) {
	MoveableEased sut;
	sut.waitInTime(1.1f);
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
}

TEST (MoveableEased, TwoWaitsLessThanWholeTime) {
	MoveableEased sut;
	sut.waitInTime(1.1f);
	sut.waitInTime(1.1f);
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
}

TEST (MoveableEased, TwoWaitsMoreThanWholeTime) {
	MoveableEased sut;
	sut.waitInTime(1.1f);
	sut.waitInTime(1.1f);
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
	EXPECT_LE(0.8f - sut.stepInTime(1.0f), 0.0000001);
}

TEST (MoveableEased, TwoWaitsMoreThanWholeTimeSmallSteps) {
	MoveableEased sut;
	sut.waitInTime(1.1f);
	sut.waitInTime(1.1f);
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.55f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.1f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_LE(0.1f - sut.stepInTime(0.2f), 0.0000001);
}

TEST (MoveableEased, OneMoveOneStepByMoreThanWholeTime) {
	MoveableEased sut;
	sut.moveByEased(1.1f, glm::vec3(0.1, 0.1, 0.2));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
}

TEST (MoveableEased, TwoMovesLessThanWholeTime) {
	MoveableEased sut;
	sut.moveByEased(1.1f, glm::vec3(0.1, 0.1, 0.2));
	sut.moveByEased(1.1f, glm::vec3(0.1, 0.1, 0.2));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
}

TEST (MoveableEased, TwoMovesMoreThanWholeTime) {
	MoveableEased sut;
	sut.moveByEased(1.1f, glm::vec3(0.1, 0.1, 0.2));
	sut.moveByEased(1.1f, glm::vec3(0.1, 0.1, 0.2));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
	EXPECT_LE(0.8f - sut.stepInTime(1.0f), 0.0000001);
}

TEST (MoveableEased, TwoMovesMoreThanWholeTimeSmallSteps) {
	MoveableEased sut;
	sut.moveByEased(1.1f, glm::vec3(0.1, 0.1, 0.2));
	sut.moveByEased(1.1f, glm::vec3(0.1, 0.1, 0.2));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.55f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.1f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_LE(0.1f - sut.stepInTime(0.2f), 0.0000001);
}

TEST (MoveableEased, OneScaleOneStepByMoreThanWholeTime) {
	MoveableEased sut;
	sut.scaleByEased(1.1f, glm::vec3(0.1, 0.1, 0.2));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
}

TEST (MoveableEased, TwoScalesLessThanWholeTime) {
	MoveableEased sut;
	sut.scaleByEased(1.1f, glm::vec3(0.1, 0.1, 0.2));
	sut.scaleByEased(1.1f, glm::vec3(0.1, 0.1, 0.2));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
}

TEST (MoveableEased, TwoScaleMoreThanWholeTime) {
	MoveableEased sut;
	sut.scaleByEased(1.1f, glm::vec3(0.1, 0.1, 0.2));
	sut.scaleByEased(1.1f, glm::vec3(0.1, 0.1, 0.2));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
	EXPECT_LE(0.8f - sut.stepInTime(1.0f), 0.0000001);
}

TEST (MoveableEased, TwoScaleMoreThanWholeTimeSmallSteps) {
	MoveableEased sut;
	sut.scaleByEased(1.1f, glm::vec3(0.1, 0.1, 0.2));
	sut.scaleByEased(1.1f, glm::vec3(0.1, 0.1, 0.2));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.55f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.1f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_LE(0.1f - sut.stepInTime(0.2f), 0.0000001);
}

TEST (MoveableEased, OneRotateOneStepByMoreThanWholeTime) {
	MoveableEased sut;
	sut.rotateByEased(1.1f, 1.0f, glm::vec3(0.1, 0.2, 0.4));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
}

TEST (MoveableEased, TwoRotateLessThanWholeTime) {
	MoveableEased sut;
	sut.rotateByEased(1.1f, 1.0f, glm::vec3(0.1, 0.2, 0.4));
	sut.rotateByEased(1.1f, 1.0f, glm::vec3(0.1, 0.2, 0.4));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
}

TEST (MoveableEased, TwoRotateMoreThanWholeTime) {
	MoveableEased sut;
	sut.rotateByEased(1.1f, 1.0f, glm::vec3(0.1, 0.2, 0.4));
	sut.rotateByEased(1.1f, 1.0f, glm::vec3(0.1, 0.2, 0.4));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
	EXPECT_EQ(0.0f, sut.stepInTime(1.0f));
	EXPECT_LE(0.8f - sut.stepInTime(1.0f), 0.0000001);
}

TEST (MoveableEased, TwoRotateMoreThanWholeTimeSmallSteps) {
	MoveableEased sut;
	sut.rotateByEased(1.1f, 1.0f, glm::vec3(0.1, 0.2, 0.4));
	sut.rotateByEased(1.1f, 1.0f, glm::vec3(0.1, 0.2, 0.4));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.55f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.1f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_EQ(0.0f, sut.stepInTime(0.5f));
	EXPECT_LE(0.1f - sut.stepInTime(0.2f), 0.0000001);
}

TEST (MoveableEased, RotateByTheSameRotation) {
	MoveableEased sut;
	sut.rotateByEased(1.1f, 0.0f, glm::vec3(1.0, 0.0, 0.0));
	sut.stepInTime(1.0f);
	EXPECT_EQ(glm::quat(1.0, 0.0, 0.0, 0.0), sut.getRotation());
}

TEST (MoveableEased, RotateByDifferentRotation) {
	MoveableEased sut;
	sut.rotateByEased(1.1f, 1.0f, glm::vec3(1.0, 0.0, 0.0));
	sut.stepInTime(1.0f);
	EXPECT_NE(glm::quat(1.0, 0.0, 0.0, 0.0), sut.getRotation());
}

TEST (MoveableEased, RotateByDifferentRotationCheckResultAfterFullStep) {
	MoveableEased sut1, sut2;
	sut2.rotateTo(glm::vec3(1.0, 0.0, 0.0), 1.0f);
	sut1.rotateByEased(1.1f, 1.0f, glm::vec3(1.0, 0.0, 0.0));
	sut1.stepInTime(1.1f);
	EXPECT_EQ(sut2.getRotation(), sut1.getRotation());
}

TEST (MoveableEased, RotateByDifferentRotationCheckResultAfterHalfStep) {
	MoveableEased sut1, sut2;
	sut2.rotateTo(glm::vec3(1.0, 0.0, 0.0), 0.5f);
	sut1.rotateByEased(1.1f, 1.0f, glm::vec3(1.0, 0.0, 0.0));
	sut1.stepInTime(0.55f);
	EXPECT_EQ(sut2.getRotation(), sut1.getRotation());
}

TEST (MoveableEased, RotateByDifferentRotationCheckResultAfterOneAndHalfStep) {
	MoveableEased sut1, sut2;
	sut2.rotateTo(glm::vec3(1.0, 0.0, 0.0), 1.5f);
	sut1.rotateByEased(1.1f, 1.0f, glm::vec3(1.0, 0.0, 0.0));
	sut1.rotateByEased(1.1f, 1.0f, glm::vec3(1.0, 0.0, 0.0));
	sut1.stepInTime(1.1f);
	sut1.stepInTime(0.55f);
	EXPECT_EQ(sut2.getRotation(), sut1.getRotation());
}

TEST (MoveableEased, MoveByTheSamePosition) {
	MoveableEased sut;
	sut.moveByEased(1.1f, glm::vec3(0.0, 0.0, 0.0));
	sut.stepInTime(1.0f);
	EXPECT_EQ(glm::vec3(0.0, 0.0, 0.0), sut.getTranslation());
}

TEST (MoveableEased, MoveByDifferentPosition) {
	MoveableEased sut;
	sut.moveByEased(1.1f, glm::vec3(1.0, 2.0, 3.0));
	sut.stepInTime(1.0f);
	EXPECT_NE(glm::vec3(1.0, 0.0, 0.0), sut.getTranslation());
}

TEST (MoveableEased, MoveByDifferentPositionCheckResultAfterFullStep) {
	MoveableEased sut1, sut2;
	sut2.moveTo(glm::vec3(1.0, 5.0, 10.0));
	sut1.moveByEased(1.1f, glm::vec3(1.0, 5.0, 10.0));
	sut1.stepInTime(1.1f);
	EXPECT_EQ(sut2.getTranslation(), sut1.getTranslation());
}

TEST (MoveableEased, MoveByDifferentPositionCheckResultAfterHalfStep) {
	MoveableEased sut1, sut2;
	sut2.moveTo(glm::vec3(0.5, 1.0, 2.0));
	sut1.moveByEased(1.1f, glm::vec3(1.0, 2.0, 4.0));
	sut1.stepInTime(0.55f);
	EXPECT_EQ(sut2.getTranslation(), sut1.getTranslation());
}

TEST (MoveableEased, MoveByDifferentPositionCheckResultAfterOneAndHalfStep) {
	MoveableEased sut1, sut2;
	sut2.moveTo(glm::vec3(1.5, 3.0, 9.0));
	sut1.moveByEased(1.1f, glm::vec3(1.0, 2.0, 6.0));
	sut1.moveByEased(1.1f, glm::vec3(1.0, 2.0, 6.0));
	sut1.stepInTime(1.1f);
	sut1.stepInTime(0.55f);
	EXPECT_EQ(sut2.getTranslation(), sut1.getTranslation());
}

TEST (MoveableEased, ScaleByTheSamePosition) {
	MoveableEased sut;
	sut.scaleByEased(1.1f, glm::vec3(0.0, 0.0, 0.0));
	sut.stepInTime(1.0f);
	EXPECT_EQ(glm::vec3(1.0, 1.0, 1.0), sut.getScale());
}

TEST (MoveableEased, ScaleByDifferentPosition) {
	MoveableEased sut;
	sut.scaleByEased(1.1f, glm::vec3(1.0, 2.0, 3.0));
	sut.stepInTime(1.0f);
	EXPECT_NE(glm::vec3(1.0, 0.0, 0.0), sut.getScale());
}

TEST (MoveableEased, ScaleByDifferentScaleCheckResultAfterFullStep) {
	MoveableEased sut1, sut2;
	sut2.scaleTo(glm::vec3(2.0, 6.0, 11.0));
	sut1.scaleByEased(1.1f, glm::vec3(1.0, 5.0, 10.0));
	sut1.stepInTime(1.1f);
	EXPECT_EQ(sut2.getScale(), sut1.getScale());
}

TEST (MoveableEased, ScaleByDifferentScaleCheckResultAfterHalfStep) {
	MoveableEased sut1, sut2;
	sut2.scaleTo(glm::vec3(0.5, 1.0, 1.5));
	sut1.scaleByEased(1.1f, glm::vec3(-1.0, 0.0, 1.0));
	sut1.stepInTime(0.55f);
	EXPECT_EQ(sut2.getScale(), sut1.getScale());
}

TEST (MoveableEased, ScaleByDifferentScaleCheckResultAfterOneAndHalfStep) {
	MoveableEased sut1, sut2;
	sut2.scaleTo(glm::vec3(2.5, 4.0, 10.0));
	sut1.scaleByEased(1.1f, glm::vec3(1.0, 2.0, 6.0));
	sut1.scaleByEased(1.1f, glm::vec3(1.0, 2.0, 6.0));
	sut1.stepInTime(1.1f);
	sut1.stepInTime(0.55f);
	EXPECT_EQ(sut2.getScale(), sut1.getScale());
}

TEST (MoveableEased, stop) {
	MoveableEased sut1, sut2;
	sut2.scaleTo(glm::vec3(2.5, 4.0, 10.0));
	sut1.scaleByEased(1.1f, glm::vec3(1.0, 2.0, 6.0));
	sut1.scaleByEased(1.1f, glm::vec3(1.0, 2.0, 6.0));
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
