/*
 * Model.h
 *
 *  Created on: Jun 12, 2014
 *      Author: Filip Wasil
 */

#ifndef MODEL_H_
#define MODEL_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/models/Programmable.h>
#include <fillwave/models/Mesh.h>
#include <fillwave/Assets.h>

namespace fillwave {
class Engine;
namespace models {
class Model;
}
namespace actions {
class TimedBoneUpdateCallback;
}
}

namespace fillwave {
typedef std::shared_ptr<models::Model> pModel;
namespace models {

/*! \class Model
 * \brief Drawable Mesh set.
 */

class Model: public Programmable {
public:

   Model(Engine* engine,
         pProgram program,
         Shape<core::VertexBasic>& shape,
         pTexture diffuseMap,
         pTexture normalMap,
         pTexture specularMap,
         const Material& material);

   Model(Engine* engine,
         pProgram program,
         const std::string& shapePath);

   Model(Engine* engine,
         pProgram program,
         const std::string& shapePath,
         const std::string& diffuseMapPath,
         const std::string& normalMapPath = "",
         const std::string& specularMapPath = "");

   Model(Engine* engine,
         pProgram program,
         const std::string& shapePath,
         pTexture diffuseMap,
         pTexture normalMap = pTexture(),
         pTexture specularMap = pTexture(),
         const Material& material = Material());

   virtual ~Model();

   void reload();

   void draw(space::Camera& camera);

   void drawDR(space::Camera& camera);

   /* Animation */
   void performAnimation(GLfloat timeElapsed_us);

   void setActiveAnimation(GLint animationID);

   GLint getActiveAnimations();

   void log();

protected:
   manager::BoneManager* mBoneManager;

   pProgram mProgramShadow,
            mProgramShadowColor;

   GLint mUniformLocationCacheBones,
   mUniformLocationCacheBonesShadow,
   mUniformLocationCacheBonesShadowColor;
private:
   /* Animation */
   GLint mActiveAnimation;

   actions::TimedBoneUpdateCallback* mAnimationCallback;

   void initUniformsCache();

   void initShadowing(Engine* engine);

   void initAnimations(const fScene* scene);

   void evaluateAnimations();

   /* Mesh tree */
   void loadNodeTransformations(fNode* node, Entity* entity);

   void loadNodes(fNode* node,
         const fScene* scene,
         Engine* engine,
         Entity* entity);

   void loadNodes(fNode* node,
         const fScene* scene,
         Engine* engine,
         Entity* entity,
         const std::string& diffuseMapPath,
         const std::string& normalMapPath,
         const std::string& specularMapPath);

   void loadNodes(fNode* node,
         const fScene* scene,
         Engine* engine,
         Entity* entity,
         pTexture diffuseMap,
         pTexture normalMap,
         pTexture specularMap,
         const Material& material);

   pMesh loadMesh(const fMesh* shape,
                  const Material& material,
                  pTextureRegion diffuseMap,
                  pTextureRegion normalMap,
                  pTextureRegion specularMap,
                  Engine* engine);
};

} /* models */

static pModel buildModel(Engine* engine,
                         pProgram program,
                         models::Shape<core::VertexBasic>& shape,
                         pTexture diffuseMap = pTexture(),
                         pTexture normalMap = pTexture(),
                         pTexture specularMap = pTexture(),
                         models::Material material = models::Material()) {
   return pModel(new models::Model (engine, program, shape, diffuseMap, normalMap, specularMap, material));
}

static pModel buildModel(Engine* engine,
                         pProgram program,
                         const std::string& shapePath,
                         const std::string& diffuseMapPath,
                         const std::string& normalMapPath = "",
                         const std::string& specularMapPath = "") {
   return pModel(new models::Model (engine, program, shapePath, diffuseMapPath, normalMapPath, specularMapPath));
}

static pModel buildModel(Engine* engine,
                         pProgram program,
                         const std::string& shapePath,
                         pTexture diffuseMap,
                         pTexture normalMap = pTexture(),
                         pTexture specularMap = pTexture(),
                         models::Material material = models::Material()) {
   return pModel(new models::Model (engine, program, shapePath, diffuseMap, normalMap, specularMap));
}

static pModel buildModel(Engine* engine,
                         pProgram program,
                         const std::string& shapePath) {
   return pModel(new models::Model (engine, program, shapePath));
}

} /* fillwave */

#endif /* MODEL_H_ */
