/*
 * Entity.h
 *
 *  Created on: 2 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <fillwave/space/Camera.h>
#include <fillwave/actions/ItemCallback.h>
#include <vector>

namespace fillwave {

namespace models {
class Entity;
}
typedef std::shared_ptr<models::Entity> pEntity;

namespace models {

/*! \class Entity
 * \brief Base for all Scene nodes.
 */

class Entity: public Moveable {
public:
	Entity(glm::vec3 translation = glm::vec3(0.0), glm::quat orientation =
			glm::quat(1.0, 0.0, 0.0, 0.0));

	virtual ~Entity();

	/* Attach/Detach */
	void attach(pEntity child);
	void detach(pEntity child);

	void onDetached();
	void onAttached(Entity* parent);

	/* Draws */

	/* Drawing */
	virtual void draw(space::Camera& camera);

	virtual void drawDR(space::Camera& camera);

	virtual void drawDepth(space::Camera& camera);

	virtual void drawDepthColor(space::Camera& camera, glm::vec3& position);

	virtual void drawAOG(space::Camera& camera);

	virtual void drawAOC(space::Camera& camera);

	virtual void drawOcclusionBox(space::Camera& camera);

	/* Flags */
	GLboolean isPSC();

	GLboolean isPSR();

	/* Callbacks */
	void handleHierarchyEvent(actions::EventType* event);
	void handlePrivateEvent(actions::EventType* event);

	/* Model */
	glm::mat4 getTransformation();

	/* Physics */
	void setTransformation(glm::mat4 modelMatrix);

	/* Callbacks */
	void attachHierarchyCallback(actions::ItemCallback* callback);
	void attachPrivateCallback(actions::ItemCallback* callback);
	void detachHierarchyCallback(actions::ItemCallback* callback);
	void detachPrivateCallback(actions::ItemCallback* callback);

	/* Parent */
	void updateMatrixTree();
	void updateParentMatrix(glm::mat4& parent);
	void updateParentRotation(glm::quat& rotation);
	glm::mat4 getParentMatrix();
	glm::quat getParentRotation();

	/* Picking */
	void pick(glm::vec3 color);
	void unpick();
	GLboolean isPickable();
	glm::vec3 getPickableColor();
	virtual void onPicked();
	virtual void onUnpicked();
	virtual void drawPicking(space::Camera& camera);

	/* External refresh */
	void setExternalRefresh(GLboolean state);
	GLboolean isExternalRefresh();
	void setExternalRefresh();

	/* Log */
	virtual void log();

protected:
	glm::quat mParentRotation;
	glm::mat4 mParentMatrix;
	glm::mat4 mTransformation;

	GLboolean mParentRefresh;
	std::vector<pEntity> mChildren;
	GLboolean mChildrenPropagateEvent;
	std::vector<actions::ItemCallback*> mCallbacksHierarchy;
	std::vector<actions::ItemCallback*> mCallbacksPrivate;

	GLboolean mPSC;
	GLboolean mPSR;

private:
	GLboolean mRefreshExternal;
	GLboolean mPickable;
	glm::vec3 mPickColor;

	void detachChildren();
	void handleEvent(
			std::vector<actions::ItemCallback*>& callbacks,
			actions::EventType* event);
	void eraseFinishedCallbacks(std::vector<actions::ItemCallback*>& callbacks);
	void detachCallback(
			std::vector<actions::ItemCallback*>& callbacks,
			actions::ItemCallback* callback);
};
} /* models */
static pEntity buildEntity() {
	return pEntity(new models::Entity());
}
} /* fillwave */

#endif /* ENTITY_H_ */
