/*
 * Entity.h
 *
 *  Created on: 2 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <fillwave/actions/callbacks/Callback.h>
#include <fillwave/common/IPickable.h>
#include <fillwave/space/base/ICamera.h>
#include <fillwave/models/base/IDrawable.h>
#include <fillwave/models/base/IRenderable.h>
#include <fillwave/models/base/TreePtr.h>

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

class Entity:
		public IRenderable,
		public IDrawable,
		public IPickable,
		public Moveable,
		public TreePtr<pEntity> {
public:
	Entity(glm::vec3 translation = glm::vec3(0.0), glm::quat orientation =
			glm::quat(1.0, 0.0, 0.0, 0.0));

	virtual ~Entity();

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

	/* IPickable */
	void pick(glm::vec3 color) override;
	void unpick() override;
	virtual void onPicked() override;
	virtual void onUnpicked() override;

	/* IDrawable */
	virtual void draw(ICamera& camera) override;
	virtual void drawPBRP(ICamera& camera) override;
	virtual void drawDR(ICamera& camera) override;
	virtual void drawDepth(ICamera& camera);
	virtual void drawDepthColor(ICamera& camera, glm::vec3& position);
	virtual void drawAOG(ICamera& camera);
	virtual void drawAOC(ICamera& camera);
	virtual void drawOcclusionBox(ICamera& camera);
	virtual void drawPicking(ICamera& camera);

	/* IRenderable */
	virtual void updateRenderer(IRenderer& renderer) override;
	virtual bool getRenderData(RenderData& renderData) override;

	/* Animations */
	virtual bool isAnimated() const;

	/* Log */
	virtual void log() const;

protected:
	/* MMC - Model Matrix Cache */
	glm::mat4 mPhysicsMMC;

	GLboolean mChildrenPropagateEvent;
	GLboolean mParentRefresh;
	std::vector<Callback*> mCallbacksHierarchy;
	std::vector<Callback*> mCallbacksPrivate;

	GLboolean mPSC;
	GLboolean mPSR;

private:
	void handleEvent(
			std::vector<Callback*>& callbacks,
			EventType& event);
	void eraseFinishedCallbacks(std::vector<Callback*>& callbacks);
	void detachCallback(
			std::vector<Callback*>& callbacks,
			Callback* callback);
};
} /* framework */
pEntity buildEntity();
} /* fillwave */

#endif /* ENTITY_H_ */
