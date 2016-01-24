/*
 * Hinge.h
 *
 *  Created on: Jan 9, 2016
 *      Author: filip
 */

#ifndef SRC_MODELS_HINGE_H_
#define SRC_MODELS_HINGE_H_

#include <fillwave/models/Entity.h>

namespace fillwave {
namespace framework {

/*! \class Hinge
 * \brief Entity capable of populating the draw method towards children.
 */

class Hinge: public Entity {
public:
	Hinge();
	virtual ~Hinge() = default;

	/* IDrawable */
	void draw(ICamera& camera);
	void drawPBRP(ICamera& camera);
	void drawDR(ICamera& camera);

	/* IRenderable */
	void updateRenderer(IRenderer& renderer) override;
	bool getRenderData(RenderData& renderData) override;
};

} /* namespace framework */
typedef std::shared_ptr<framework::Hinge> pHinge;
static pHinge buildHinge() {
	return pHinge(new framework::Hinge());
}
} /* namespace fillwave */

#endif /* SRC_MODELS_HINGE_H_ */
