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
	   core::Program* program,
	   framework::Shape<core::VertexBasic>& shape,
	   core::Texture2D* diffuseMap,
	   core::Texture2D* normalMap,
	   core::Texture2D* specularMap,
	   const Material& material);

	Model(Engine* engine, core::Program* program, const std::string& shapePath);

	Model(
	   Engine* engine,
	   core::Program* program,
	   const std::string& shapePath,
	   const std::string& diffuseMapPath,
	   const std::string& normalMapPath = "",
	   const std::string& specularMapPath = "");

	Model(
	   Engine* engine,
	   core::Program* program,
	   const std::string& shapePath,
	   core::Texture2D* diffuseMap,
	   core::Texture2D* normalMap = nullptr,
	   core::Texture2D* specularMap = nullptr,
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

	void updateRenderer(IRenderer& renderer) override;

	void log() const;

 protected:
	Animator* mAnimator;
	LightSystem* mLights;
	core::Program *mProgramShadow, *mProgramShadowColor;
	GLint mUniformLocationCacheBones, mUniformLocationCacheBonesShadow,
	      mUniformLocationCacheBonesShadowColor;
 private:
	/* Animation */
	GLint mActiveAnimation;
	Engine* mEngine;

	/* Init */
	void initUniformsCache();
	void initShadowing(Engine* engine);
	void evaluateAnimations();

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
	void initAnimations(const aiScene* scene);
	/* Tree */
	void loadNodeTransformations(aiNode* node, Entity* entity);

	void loadNodes(
	   aiNode* node,
	   const aiScene* scene,
	   Engine* engine,
	   Entity* entity);

	void loadNodes(
	   aiNode* node,
	   const aiScene* scene,
	   Engine* engine,
	   Entity* entity,
	   const std::string& diffuseMapPath,
	   const std::string& normalMapPath,
	   const std::string& specularMapPath);

	void loadNodes(
	   aiNode* node,
	   const aiScene* scene,
	   Engine* engine,
	   Entity* entity,
	   core::Texture2D* diffuseMap,
	   core::Texture2D* normalMap,
	   core::Texture2D* specularMap,
	   const Material& material);

	puMesh loadMesh(
	   const aiMesh* shape,
	   const Material& material,
	   core::Texture2D* diffuseMap,
	   core::Texture2D* normalMap,
	   core::Texture2D* specularMap,
	   Engine* engine);
#else /* FILLWAVE_MODEL_LOADER_ASSIMP */
	puMesh loadMesh(tinyobj::shape_t& shape,
	                const Material& material,
	                core::Texture2D* diffuseMap,
	                core::Texture2D* normalMap,
	                core::Texture2D* specularMap,
	                Engine* engine);
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

};

} /* framework */

typedef std::unique_ptr<framework::Model> puModel;

puModel buildModel(
   Engine* engine,
   core::Program* program,
   framework::Shape<core::VertexBasic>& shape,
   core::Texture2D* diffuseMap = nullptr,
   core::Texture2D* normalMap = nullptr,
   core::Texture2D* specularMap = nullptr,
   framework::Material material = framework::Material());

puModel buildModel(
   Engine* engine,
   core::Program* program,
   const std::string& shapePath,
   const std::string& diffuseMapPath,
   const std::string& normalMapPath = "",
   const std::string& specularMapPath = "");

puModel buildModel(
   Engine* engine,
   core::Program* program,
   const std::string& shapePath,
   core::Texture2D* diffuseMap,
   core::Texture2D* normalMap = nullptr,
   core::Texture2D* specularMap = nullptr,
   framework::Material material = framework::Material());

puModel buildModel(
   Engine* engine,
   core::Program* program,
   const std::string& shapePath);

} /* fillwave */

#endif /* MODEL_H_ */
