/*
 * Entity.h
 *
 *  Created on: 2 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <fillwave/actions/Callback.h>
#include <fillwave/space/Camera.h>
#include <vector>
#include <map>

namespace fillwave {

namespace models {
class Entity;
}

namespace core {
class Program;
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

	/* Flags */
	GLboolean isPSC();
	GLboolean isPSR();

	/* Callbacks */
	void handleHierarchyEvent(actions::EventType& event);
	void handlePrivateEvent(actions::EventType& event);

	/* Model */
	glm::mat4 getPhysicsMMC();

	/* Physics */
	void setTransformation(glm::mat4 modelMatrix);

	/* Callbacks */
	void attachHierarchyCallback(actions::Callback* callback);
	void attachPrivateCallback(actions::Callback* callback);
	void detachHierarchyCallback(actions::Callback* callback);
	void detachPrivateCallback(actions::Callback* callback);

	/* Parent */
	void updateMatrixTree();
	void updateParentMatrix(glm::mat4& parent);
	void updateParentRotation(glm::quat& rotation);

	/* Picking */
	void pick(glm::vec3 color);
	void unpick();
	GLboolean isPickable();
	glm::vec3 getPickableColor();

	/* Draw */
	virtual void draw(space::Camera& camera);
	virtual void drawPBRP(space::Camera& camera);
	virtual void drawDR(space::Camera& camera);
	virtual void drawDepth(space::Camera& camera);
	virtual void drawDepthColor(space::Camera& camera, glm::vec3& position);
	virtual void drawAOG(space::Camera& camera);
	virtual void drawAOC(space::Camera& camera);
	virtual void drawOcclusionBox(space::Camera& camera);

	/* Pick */
	virtual void onPicked();
	virtual void onUnpicked();
	virtual void drawPicking(space::Camera& camera);
	virtual void updateRenderpass(std::map<GLuint, std::vector<Entity*> >& renderpasses);

	/* Log */
	virtual void log();

protected:
	/* MMC - Model Matrix Cache */
	glm::mat4 mPhysicsMMC;

	GLboolean mChildrenPropagateEvent;
	GLboolean mParentRefresh;
	std::vector<pEntity> mChildren;
	std::vector<actions::Callback*> mCallbacksHierarchy;
	std::vector<actions::Callback*> mCallbacksPrivate;

	GLboolean mPSC;
	GLboolean mPSR;
	GLboolean mFlagUpdateRenderPass;

private:
	GLboolean mPickable;
	glm::vec3 mPickColor;

	void detachChildren();
	void handleEvent(
			std::vector<actions::Callback*>& callbacks,
			actions::EventType& event);
	void eraseFinishedCallbacks(std::vector<actions::Callback*>& callbacks);
	void detachCallback(
			std::vector<actions::Callback*>& callbacks,
			actions::Callback* callback);
};
} /* models */
static pEntity buildEntity() {
	return pEntity(new models::Entity());
}
} /* fillwave */

#endif /* ENTITY_H_ */
