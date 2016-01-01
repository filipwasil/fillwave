/*
 * Entity.h
 *
 *  Created on: 2 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <fillwave/actions/callbacks/Callback.h>
#include <fillwave/space/Camera.h>
#include <vector>
#include <map>

namespace fillwave {

namespace framework {
class Entity;
}

namespace core {
class Program;
}

typedef std::shared_ptr<framework::Entity> pEntity;

namespace framework {

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
	void handleHierarchyEvent(EventType& event);
	void handlePrivateEvent(EventType& event);

	/* Model */
	glm::mat4 getPhysicsMMC();

	/* Physics */
	void setTransformation(glm::mat4 modelMatrix);

	/* Callbacks */
	void attachHierarchyCallback(Callback* callback);
	void attachPrivateCallback(Callback* callback);
	void detachHierarchyCallback(Callback* callback);
	void detachPrivateCallback(Callback* callback);

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
	virtual void draw(Camera& camera);
	virtual void drawPBRP(Camera& camera);
	virtual void drawDR(Camera& camera);
	virtual void drawDepth(Camera& camera);
	virtual void drawDepthColor(Camera& camera, glm::vec3& position);
	virtual void drawAOG(Camera& camera);
	virtual void drawAOC(Camera& camera);
	virtual void drawOcclusionBox(Camera& camera);
	virtual void drawPicking(Camera& camera);

	/* Pick */
	virtual void onPicked();
	virtual void onUnpicked();
	virtual void updateRenderpass(std::map<GLuint, std::vector<Entity*> >& renderpasses);

	/* Log */
	virtual void log();

protected:
	/* MMC - Model Matrix Cache */
	glm::mat4 mPhysicsMMC;

	GLboolean mChildrenPropagateEvent;
	GLboolean mParentRefresh;
	std::vector<pEntity> mChildren;
	std::vector<Callback*> mCallbacksHierarchy;
	std::vector<Callback*> mCallbacksPrivate;

	GLboolean mPSC;
	GLboolean mPSR;
	GLboolean mFlagUpdateRenderPass;

private:
	GLboolean mPickable;
	glm::vec3 mPickColor;

	void detachChildren();
	void handleEvent(
			std::vector<Callback*>& callbacks,
			EventType& event);
	void eraseFinishedCallbacks(std::vector<Callback*>& callbacks);
	void detachCallback(
			std::vector<Callback*>& callbacks,
			Callback* callback);
};
} /* framework */
static pEntity buildEntity() {
	return pEntity(new framework::Entity());
}
} /* fillwave */

#endif /* ENTITY_H_ */
