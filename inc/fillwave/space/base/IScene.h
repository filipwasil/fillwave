/*
 * IScene.h
 *
 *  Created on: May 2, 2014
 *      Author: Filip Wasil
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

/*! \class IScene
 * \brief Entity to be a root of Entity tree.
 */

class IScene: public TreePtr<Entity> {
 public:
	IScene(IRenderer* renderer = new RendererFR());

	virtual ~IScene() = default;

	void updateDependencies();
	void updateRenderer();
	void setRenderer(IRenderer* renderer);
	void resetRenderer(GLuint screenWidth, GLuint screenHeight);

	/* Cursor */
	void setCursor(pCursor& cursor);
	pCursor getCursor();
	void drawCursor();
	void moveCursor(glm::vec2 position);

	/* Scene */
	void setSkybox(pSkybox& skybox);
	void setAmbient(glm::vec3 cursor);
	void setHUD(pHUD& hud);

	/* Pickable */
	void registerPickable(Entity* entity);
	void pick(glm::ivec4 color);

	/* Events */
	void onEvent(EventType& event);

	void draw(ICamera& c);
	void drawHUD();
	void drawDepth(ICamera& camera);
	void drawDepthColor(ICamera& camera, glm::vec3& position);

	/* Interface */
	void draw();
	void drawDepthInt();
	void drawPicking();
	void drawOcclusion();
	ICamera* getCamera();
	void setCamera(puICamera&& camera);

	/* Optional */
	virtual void onShow();
	virtual void onHide();

 protected:
	pCursor mCursor;
	pSkybox mSkybox;
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
typedef std::unique_ptr<framework::IScene> puIScene;
} /* fillwave */

#endif /* SCENE_H_ */
