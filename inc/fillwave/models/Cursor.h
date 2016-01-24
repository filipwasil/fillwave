/*
 * Cursor.h
 *
 *  Created on: Nov 6, 2014
 *      Author: Filip Wasil
 */

#ifndef CURSOR_H_
#define CURSOR_H_

#include <fillwave/models/Impostor.h>

namespace fillwave {
class Engine;
namespace framework {

/*! \class Cursor
 * \brief Impostor to handle custom cursor instead of the standard one.
 */

class Cursor: public Impostor {
public:
	Cursor(Engine* engine, pTexture texture);
	virtual ~Cursor() = default;

	void move(glm::vec2 position);
	void draw();

private:
	GLfloat mScreenFactor;
	GLint mULCPosition, mULCScreenFactor, mULCTextureUnit, mULCSize;

	void initUniformsCache();
	bool getRenderData(RenderData& renderData) override;
};

} /* framework */
typedef std::shared_ptr<framework::Cursor> pCursor;

pCursor buildCursor(Engine* engine, pTexture texture);

} /* fillwave */

#endif /* CURSOR_H_ */
