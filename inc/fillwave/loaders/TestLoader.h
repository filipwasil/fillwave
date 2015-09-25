/*
 * TestLoader.h
 *
 *  Created on: Jun 9, 2014
 *      Author: filip
 */

#ifndef TestLoader_H_
#define TestLoader_H_

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

#include <fillwave/OpenGL.h>
#include <fillwave/Assets.h>

namespace fillwave {
namespace loader {

/*! \class TestLoader
 * \brief Tests model using asset loader.
 */

class TestLoader {
private:
   const std::string mFileName;
public:
   TestLoader(const std::string& pFile);
   virtual ~TestLoader();
   void testFile();
   void testScene(const fScene* assimpScene);
   void printVertices(const fScene* assimpScene, GLint meshID);
   void printNormals(const fScene* assimpScene, GLint meshID);
   void printUV(const fScene* assimpScene, GLint meshID);
   void printTangents(const fScene* assimpScene, GLint meshID);
   void printBitangents(const fScene* assimpScene, GLint meshID);
   void printIndices(const fScene* assimpScene, GLint meshID);
   void printInfoShort(const fScene* assimpScene, GLint meshID);

   void printNameNode(aiNode* node, GLint recursion);
   void printTree(const fScene* assimpScene);
   void printNamesMesh(const fScene* assimpScene);
};

} /* loader */
} /* fillwave */

#endif /* TestLoader_H_ */
