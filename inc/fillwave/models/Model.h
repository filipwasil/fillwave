/*
 * Model.h
 *
 *  Created on: Jun 12, 2014
 *      Author: Filip Wasil
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <fillwave/models/base/Programmable.h>
#include <fillwave/models/Mesh.h>
#include <fillwave/Assets.h>

namespace fillwave {
class Engine;
namespace framework {

class TimedBoneUpdateCallback;

/*! \class Model
 * \brief Drawable Mesh set.
 */

class Model: public Programmable {
public:

	Model(
			Engine* engine,
			pProgram program,
			framework::Shape<core::VertexBasic>& shape,
			pTexture2D diffuseMap,
			pTexture2D normalMap,
			pTexture2D specularMap,
			const Material& material);

	Model(Engine* engine, pProgram program, const std::string& shapePath);

	Model(
			Engine* engine,
			pProgram program,
			const std::string& shapePath,
			const std::string& diffuseMapPath,
			const std::string& normalMapPath = "",
			const std::string& specularMapPath = "");

	Model(
			Engine* engine,
			pProgram program,
			const std::string& shapePath,
			pTexture2D diffuseMap,
			pTexture2D normalMap = pTexture2D(),
			pTexture2D specularMap = pTexture2D(),
			const Material& material = Material());

	virtual ~Model();

	bool isAnimated() const;

	void reload();

	void draw(ICamera& camera);
	void drawPBRP(ICamera& camera);
	void drawDR(ICamera& camera);

	/* Animation */
	void performAnimation(GLfloat timeElapsed_us);
	void setActiveAnimation(GLint animationID);
	GLint getActiveAnimations();

	void updateRenderer(IRenderer& renderer);

	void log() const;

protected:
	Animator* mAnimator;
	LightManager* mLightManager;
	pProgram mProgramShadow, mProgramShadowColor;
	GLint mUniformLocationCacheBones, mUniformLocationCacheBonesShadow,
			mUniformLocationCacheBonesShadowColor;
private:
	/* Animation */
	TimedBoneUpdateCallback* mAnimationCallback;
	GLint mActiveAnimation;

	/* Init */
	void initUniformsCache();
	void initShadowing(Engine* engine);
	void initAnimations(const fScene* scene);
	void evaluateAnimations();

	/* Tree */
	void loadNodeTransformations(fNode* node, Entity* entity);

	void loadNodes(
			fNode* node,
			const fScene* scene,
			Engine* engine,
			Entity* entity);

	void loadNodes(
			fNode* node,
			const fScene* scene,
			Engine* engine,
			Entity* entity,
			const std::string& diffuseMapPath,
			const std::string& normalMapPath,
			const std::string& specularMapPath);

	void loadNodes(
			fNode* node,
			const fScene* scene,
			Engine* engine,
			Entity* entity,
			pTexture2D diffuseMap,
			pTexture2D normalMap,
			pTexture2D specularMap,
			const Material& material);

	pMesh loadMesh(
			const fMesh* shape,
			const Material& material,
			pTextureRegion diffuseMap,
			pTextureRegion normalMap,
			pTextureRegion specularMap,
			Engine* engine);
};

} /* framework */

typedef std::shared_ptr<framework::Model> pModel;

pModel buildModel(
		Engine* engine,
		pProgram program,
		framework::Shape<core::VertexBasic>& shape,
		pTexture2D diffuseMap = pTexture2D(),
		pTexture2D normalMap = pTexture2D(),
		pTexture2D specularMap = pTexture2D(),
		framework::Material material = framework::Material());

pModel buildModel(
		Engine* engine,
		pProgram program,
		const std::string& shapePath,
		const std::string& diffuseMapPath,
		const std::string& normalMapPath = "",
		const std::string& specularMapPath = "");

pModel buildModel(
		Engine* engine,
		pProgram program,
		const std::string& shapePath,
		pTexture2D diffuseMap,
		pTexture2D normalMap = pTexture2D(),
		pTexture2D specularMap = pTexture2D(),
		framework::Material material = framework::Material());

pModel buildModel(
		Engine* engine,
		pProgram program,
		const std::string& shapePath);

} /* fillwave */

#endif /* MODEL_H_ */
