/*
 * Bone.h
 *
 *  Created on: Jun 23, 2014
 *      Author: Filip Wasil
 */

#ifndef BONE_H_
#define BONE_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/models/Entity.h>
#include <fillwave/Assets.h>

namespace fillwave {

namespace animation {
class Bone;
}

typedef std::shared_ptr<animation::Bone> pBone;

namespace animation {

/*! \class Bone
 * \brief Entity used by BoneManager to perform animation.
 */

class Bone: public models::Entity {
public:
	Bone(fBone* assimpBone);
	virtual ~Bone();
	void setName(std::string name);
	std::string getName();
	void childrenUpdate();

	glm::mat4 getOffsetMatrix();
	glm::mat4 getGlobalOffsetMatrix();
	void setOffsetMatrix(glm::mat4 m);
	void setGlobalOffsetMatrix(glm::mat4 m);

	void log();

private:
	std::string mName;
	glm::mat4 mOffsetMatrix;
	glm::mat4 mGlobalOffsetMatrix;
};

} /* animation */
} /* fillwave */

#endif /* BONE_H_ */
