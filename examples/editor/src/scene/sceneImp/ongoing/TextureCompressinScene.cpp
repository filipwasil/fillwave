//============================================================================
// Name        : example_texture_compression.cpp
// Author      : Filip Wasil
// Version     :
// Copyright   : none
// Description : Fillwave engine example texture compression
//============================================================================

#include <ContextGLFW.h>
#include <example.h>

/* Graphics */
#include <fillwave/Fillwave.h>


/* Physics */
//#include <bullet>

using namespace flw;
using namespace flw::flf;
using namespace std;

FLOGINIT("Test app", FERROR | FFATAL)

int main(int argc, char* argv[]) {
	ContextGLFW mContext;
	mEngine = new Engine(argc, argv);
	mEngine->insertResizeScreen(mContext.getScreenWidth(),
	      mContext.getScreenHeight());

	/* Scene and camera */
	mEngine->setCurrentScene(make_unique<Scene>());
	mEngine->getCurrentScene().setCamera(
	   make_unique<CameraPerspective>());

	/* Models */
	scene->attach(make_unique<Model>(mEngine,
	                                 ProgramLoader(mEngine).getDefault(),
	                                 "meshes/sphere.obj", "textures/compression/.color"));

	mContext.render();
	delete mEngine;
	exit(EXIT_SUCCESS);
}
