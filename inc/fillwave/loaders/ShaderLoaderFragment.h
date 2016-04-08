/*
 * ShaderLoaderFragment.h
 *
 *  Created on: 13 May 2015
 *      Author: Filip Wasil
 */

#ifndef SHADERLOADERFRAGMENT_H_
#define SHADERLOADERFRAGMENT_H_

#include <fillwave/loaders/ShaderLoader.h>
#include <fillwave/OpenGL.h>

namespace fillwave {
namespace framework {

/*! \class ShaderLoaderFragment
 * \brief ShaderLoader to load fragment shader sources.
 */

class ShaderLoaderFragment: public ShaderLoader {
  public:
	ShaderLoaderFragment(GLuint renderTargets = 1);

	virtual ~ShaderLoaderFragment() = default;

	const std::string getSource() const;

  private:
	GLboolean mFog;
	GLboolean mColor;
	GLboolean mColorBoost;
	GLboolean mTextureOnly;
	GLboolean mPointLights;
	GLuint mRendertargets;
};

} /* framework */
} /* fillwave */

#endif /* SHADERLOADERFRAGMENT_H_ */
