/*
 * IScene.h
 *
 *  Created on: May 2, 2014
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <fillwave/hud/base/HUD.h>
#include <fillwave/models/Entity.h>
#include <fillwave/models/Skybox.h>
#include <fillwave/models/Cursor.h>
#include <fillwave/models/Terrain.h>
#include <fillwave/models/base/IDrawable.h>
#include <fillwave/renderers/RendererFR.h>
#include <unordered_map>

namespace fillwave {
namespace framework {

/*! \class Scene
 * \brief Entity to be a root of Entity tree.
 */

class Scene: public TreePtr<Entity> {
 public:
	Scene(IRenderer* renderer = new RendererFR());

	virtual ~Scene() = default;

	void updateDependencies();
	void updateRenderer();
	void setRenderer(IRenderer* renderer);
	void resetRenderer(GLuint screenWidth, GLuint screenHeight);

	/* Cursor */
	void setCursor(puCursor&& cursor);
	Cursor& getCursor();
	void drawCursor();

	/* Camera */
	ICamera& getCamera();
	void setCamera(puICamera&& camera);

	/* Scene */
	void setSkybox(puSkybox&& skybox);
	void setHUD(pHUD hud);
	void setAmbient(glm::vec3 cursor);

	/* Pickable */
	void registerPickable(Entity* entity);
	void pick(glm::ivec4 color);

	/* Events */
	void onEvent(EventType& event);

	void draw(ICamera& c);
	void drawHUD();
	void drawDepth(ICamera& camera);
	void drawDepthColor(ICamera& camera, glm::vec3& position);

	/* Draw */
	void draw();
	void drawDepthInt();
	void drawPicking();
	void drawOcclusion();

	/* Interface */
	virtual void onShow();
	virtual void onHide();

 protected:
	puCursor mCursor;
	puSkybox mSkybox;
	std::unordered_map<GLint, Entity*> mPickingTable;
	Entity* mLastPicked;
	glm::vec3 mAmbientGlobal;
	puIRenderer mRenderer;
	pHUD mHUD;
	puICamera mCamera;

 private:
	const GLint MAXIMUM_TRIALS_TO_PICK_COLOR = 2000;
};

} /* framework */
typedef std::unique_ptr<framework::Scene> puScene;
} /* fillwave */

#endif /* SCENE_H_ */
