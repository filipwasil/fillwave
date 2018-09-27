#pragma once

/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* Space */
#include <flw/flf/space/LightPoint.h>
#include <flw/flf/space/LightSpot.h>
#include <flw/flf/space/LightDirectional.h>
#include <flw/flf/space/Scene.h>

/* Loaders */
#include <flw/flf/loaders/AndroidLoader.h>
#include <flw/flf/loaders/ProgramLoader.h>

/* Models */
#include <flw/flf/models/builders/BuilderModelManual.h>
#include <flw/flf/models/builders/BuilderModelExternalMaps.h>
#include <flw/flf/models/shapes/BoxOcclusion.h>
#include <flw/flf/models/shapes/Box.h>
#include <flw/flf/models/Skybox.h>
#include <flw/flf/models/MeshTerrain.h>

/* HUD */
#include <flw/flf/hud/Text.h>
#include <flw/flf/hud/Button.h>

/* Effects */
#include <flw/flf/models/effects/Fog.h>
#include <flw/flf/models/effects/BoostColor.h>
#include <flw/flf/models/effects/TextureOnly.h>

/* Particles */
#include <flw/flf/models/Impostor.h>
#include <flw/flf/models/EmiterPointCPU.h>

#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#else
#include <flw/flf/models/extended/EmiterPointGPU.h>
#endif