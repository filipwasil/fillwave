/*
 * IRenderable.h
 *
 *  Created on: Jan 23, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_MODELS_BASE_IRENDERABLE_H_
#define INC_FILLWAVE_MODELS_BASE_IRENDERABLE_H_

#include <fillwave/models/base/RenderItem.h>
#include <fillwave/models/base/IDrawable.h>

namespace fillwave {
namespace framework {

class IRenderer;

/*! \class IRenderable
 * \brief Encapsulates renderable objects. To be used with IRenderer.
 */

class IRenderable: public IDrawable {
 public:
	IRenderable() = default;
	virtual ~IRenderable() = default;
	virtual bool getRenderItem(RenderItem& item) = 0;
	virtual void updateRenderer(IRenderer& renderer) = 0;
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_MODELS_BASE_IRENDERABLE_H_ */
