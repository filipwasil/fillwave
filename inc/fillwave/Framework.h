/*
 * framework.h
 *
 *  Created on: Jan 17, 2016
 *      Author: filip
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef INC_FILLWAVE_FRAMEWORK_H_
#define INC_FILLWAVE_FRAMEWORK_H_

/* Events */
#include <fillwave/actions/callbacks/FPSCallback.h>
#include <fillwave/actions/callbacks/TimedMoveCallback.h>
#include <fillwave/actions/callbacks/TimedRotateCallback.h>
#include <fillwave/actions/callbacks/TimedScaleCallback.h>
#include <fillwave/actions/callbacks/TimedCallback.h>
#include <fillwave/actions/callbacks/TimedEmiterUpdateCallback.h>
#include <fillwave/actions/callbacks/LoopCallback.h>
#include <fillwave/actions/callbacks/SequenceCallback.h>
#include <fillwave/actions/events/CharacterModsTEvent.h>
#include <fillwave/actions/events/CharacterTEvent.h>
#include <fillwave/actions/events/CursorEnterTEvent.h>
#include <fillwave/actions/events/CursorPositionTEvent.h>
#include <fillwave/actions/events/CursorPositionTEvent.h>
#include <fillwave/actions/events/KeyboardTEvent.h>
#include <fillwave/actions/events/MouseButtonTEvent.h>
#include <fillwave/actions/events/ScrollTEvent.h>
#include <fillwave/actions/events/TimeTEvent.h>
#include <fillwave/actions/events/TouchTEvent.h>

/* Space */
#include <fillwave/space/LightPoint.h>
#include <fillwave/space/LightSpot.h>
#include <fillwave/space/LightDirectional.h>

/* Loaders */
#include <fillwave/loaders/FileLoader.h>
#include <fillwave/loaders/AndroidLoader.h>
#include <fillwave/loaders/ProgramLoader.h>

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
