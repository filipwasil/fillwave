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
#include <fillwave/models/base/IRenderable.h>
#include <fillwave/common/IFocusable.h>
#include <fillwave/models/base/TreePtr.h>

namespace fillwave {

namespace framework {
class Entity;
}

namespace core {
class Program;
}

typedef std::unique_ptr<framework::Entity> puEntity;

namespace framework {

/*! \class Entity
 * \brief Base for all Scene nodes.
 */

class Entity:
	public IRenderable, public IPickable, public Moveable,
	public TreePtr<Entity> {
 public:
	Entity(glm::vec3 translation = glm::vec3(0.0), glm::quat orientation =
	          glm::quat(1.0, 0.0, 0.0, 0.0));

	virtual ~Entity();

	/* Flags */
	GLboolean isPSC();
	GLboolean isPSR();

	/* Callbacks */
	void handleHierarchyEvent(EventType& event);

	/* Model */
	glm::mat4 getPhysicsMMC();

	/* Physics */
	void setTransformation(glm::mat4 modelMatrix);

	/* Callbacks */
	void attachHierarchyCallback(puCallback&& callback);
	void detachHierarchyCallback(Callback* callback);

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
	virtual void drawDepth(ICamera& camera) override;
	virtual void drawDepthColor(ICamera& camera, glm::vec3& position) override;
	virtual void drawAOG(ICamera& camera) override;
	virtual void drawAOC(ICamera& camera) override;
	virtual void drawOcclusionBox(ICamera& camera) override;
	virtual void drawPicking(ICamera& camera) override;

	/* IRenderable */
	virtual void updateRenderer(IRenderer& renderer) override;
	virtual bool getRenderItem(RenderItem& item) override;

	/* Animations */
	virtual bool isAnimated() const;

	/* Log */
	virtual void log() const;

 protected:
	/* MMC - Model Matrix Cache */
	glm::mat4 mPhysicsMMC;

	GLboolean mChildrenPropagateEvent;
	GLboolean mParentRefresh;
	std::vector<puCallback> mCallbacksHierarchy;

	GLboolean mPSC;
	GLboolean mPSR;

 private:
	void eraseFinishedCallbacks(std::vector<puCallback>& callbacks);
	void detachCallback(std::vector<puCallback>& callbacks, Callback* callback);
};
} /* framework */
puEntity buildEntity();
} /* fillwave */

#endif /* ENTITY_H_ */
