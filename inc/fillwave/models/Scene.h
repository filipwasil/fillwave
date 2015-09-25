/*
 * Scene.h
 *
 *  Created on: May 2, 2014
 *      Author: Filip Wasil
 */

#ifndef SCENE_H_
#define SCENE_H_

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
#include <fillwave/models/Skybox.h>
#include <fillwave/particles/Cursor.h>
#include <fillwave/terrain/Terrain.h>

namespace fillwave {
namespace models {

/*! \class Scene
 * \brief Entity to be a root of Entity tree.
 *
 */

//#define MAXIMUM_PICKABLE_SLOTS 768
//#define MAXIMUM_TRIALS_TO_PICK_COLOR 2000
class Scene: public Entity {
public:
	Scene();

	virtual ~Scene();

	void setCursor(pCursor cursor);

	void setSkybox(pSkybox skybox);

	glm::vec3 getAmbient();

	void setAmbient(glm::vec3 cursor);

	pCursor getCursor();

	virtual void draw() = 0;

	virtual void drawDR() = 0;

	virtual void drawAOG() = 0;

	virtual void drawAOC() = 0;

	virtual void drawDepthInt() = 0;

	virtual void drawPicking() = 0;

	virtual void drawSkybox() = 0;

	virtual void drawOcclusion() = 0;

	virtual pCamera getCamera() = 0;

	void drawCursor();

	void drawFromCustomCamera(space::Camera& c);

	void moveCursor(glm::vec2 position);

	void registerPickable(pEntity entity);

	void pick(glm::ivec4 color);

	virtual void onShow() {
		(void) this;
	}

	virtual void onHide() {
		(void) this;
	}

protected:
	pCursor mCursor;
	pSkybox mSkybox;
	std::map<GLint, pEntity> mPickingTable;
	pEntity mLastPicked;
	glm::vec3 mAmbientGlobal;

private:
	const GLint MAXIMUM_TRIALS_TO_PICK_COLOR = 2000;
};

} /* models */
typedef std::shared_ptr<models::Scene> pScene;
} /* fillwave */

#endif /* SCENE_H_ */
