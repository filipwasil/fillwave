/*
 * framework.h
 *
 *  Created on: Jan 17, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_FRAMEWORK_H_
#define INC_FILLWAVE_FRAMEWORK_H_

/* Events */
#include <fillwave/actions/events/TimeEvent.h>
#include <fillwave/actions/events/TouchEvent.h>
#include <fillwave/actions/events/ScrollEvent.h>
#include <fillwave/actions/events/CursorEnterEvent.h>
#include <fillwave/actions/events/CursorPositionEvent.h>
#include <fillwave/actions/events/CharacterEvent.h>
#include <fillwave/actions/events/CharacterModsEvent.h>
#include <fillwave/actions/events/CursorPositionEvent.h>
#include <fillwave/actions/events/MouseButtonEvent.h>
#include <fillwave/actions/events/KeyboardEvent.h>

/* Callbacks */
#include <fillwave/actions/callbacks/FPSCallback.h>
#include <fillwave/actions/callbacks/TimedMoveCallback.h>
#include <fillwave/actions/callbacks/TimedRotateCallback.h>
#include <fillwave/actions/callbacks/TimedScaleCallback.h>
#include <fillwave/actions/callbacks/TimedCallback.h>
#include <fillwave/actions/callbacks/TimedEmiterUpdateCallback.h>
#include <fillwave/actions/callbacks/LoopCallback.h>
#include <fillwave/actions/callbacks/SequenceCallback.h>

/* Space */
#include <fillwave/space/SceneOrthographic.h>
#include <fillwave/space/ScenePerspective.h>
#include <fillwave/space/LightPoint.h>
#include <fillwave/space/LightSpot.h>
#include <fillwave/space/LightDirectional.h>

/* Loaders */
#include <fillwave/loaders/FileLoader.h>
#include <fillwave/loaders/AndroidLoader.h>

/* Common */
#include <fillwave/common/PhysicsMeshBuffer.h>

/* Models */
#include <fillwave/models/builders/BuilderModelManual.h>
#include <fillwave/models/builders/BuilderModelExternalMaps.h>
#include <fillwave/models/shapes/BoxOcclusion.h>
#include <fillwave/models/shapes/Box.h>
#include <fillwave/models/Skybox.h>
#include <fillwave/models/Terrain.h>
#include <fillwave/models/MeshTerrain.h>

/* HUD */
//#include <fillwave/hud/Text.h>
#include <fillwave/hud/Button.h>
#include <fillwave/hud/ProgressBar.h>

/* Effects */
#include <fillwave/models/effects/Fog.h>
#include <fillwave/models/effects/BoostColor.h>
#include <fillwave/models/effects/TextureOnly.h>

/* Particles */
#include <fillwave/models/Impostor.h>
#include <fillwave/models/EmiterPointGPU.h>
#include <fillwave/models/EmiterPointCPU.h>

#endif /* INC_FILLWAVE_FRAMEWORK_H_ */
