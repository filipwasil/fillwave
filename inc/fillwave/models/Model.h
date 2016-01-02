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
			pTexture diffuseMap,
			pTexture normalMap,
			pTexture specularMap,
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
			pTexture diffuseMap,
			pTexture normalMap = pTexture(),
			pTexture specularMap = pTexture(),
			const Material& material = Material());

	virtual ~Model();

	void reload();

	void draw(ICamera& camera);
	void drawPBRP(ICamera& camera);
	void drawDR(ICamera& camera);

	/* Animation */
	void performAnimation(GLfloat timeElapsed_us);
	void setActiveAnimation(GLint animationID);
	GLint getActiveAnimations();

	void log();

protected:
	Animator* mAnimator;
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
			pTexture diffuseMap,
			pTexture normalMap,
			pTexture specularMap,
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

static pModel buildModel(
		Engine* engine,
		pProgram program,
		framework::Shape<core::VertexBasic>& shape,
		pTexture diffuseMap = pTexture(),
		pTexture normalMap = pTexture(),
		pTexture specularMap = pTexture(),
		framework::Material material = framework::Material()) {
	return pModel(
			new framework::Model(engine, program, shape, diffuseMap, normalMap,
					specularMap, material));
}

static pModel buildModel(
		Engine* engine,
		pProgram program,
		const std::string& shapePath,
		const std::string& diffuseMapPath,
		const std::string& normalMapPath = "",
		const std::string& specularMapPath = "") {
	return pModel(
			new framework::Model(engine, program, shapePath, diffuseMapPath,
					normalMapPath, specularMapPath));
}

static pModel buildModel(
		Engine* engine,
		pProgram program,
		const std::string& shapePath,
		pTexture diffuseMap,
		pTexture normalMap = pTexture(),
		pTexture specularMap = pTexture(),
		framework::Material material = framework::Material()) {
	return pModel(
			new framework::Model(engine, program, shapePath, diffuseMap, normalMap,
					specularMap, material));
}

static pModel buildModel(
		Engine* engine,
		pProgram program,
		const std::string& shapePath) {
	return pModel(new framework::Model(engine, program, shapePath));
}

} /* fillwave */

#endif /* MODEL_H_ */
