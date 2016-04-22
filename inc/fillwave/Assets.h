/*
 * Assets.h
 *
 *  Created on: Jun 9, 2014
 *      Author: Filip Wasil
 *
 * Fillwave C++11 graphics Engine
 *
 * Copyright (C) 2016 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This library is available free of charge for any commercial
 * or non-commercial use. However, You are obligated to put a clearly
 * visible information in Your license agreement that Your Software
 * uses Fillwave library to handle graphics management.
 * If You are interested in extra support, extra features
 * or cooperation I look forward to hearing from You.
 *
 * fillwave@gmail.com
 *
 */


#ifndef FILLWAVE_ASSETS_H_
#define FILLWAVE_ASSETS_H_

#include <fillwave/Config.h>

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include <assimp/material.h>
#else
#include <tinyobjloader/tiny_obj_loader.h>
#endif

//constexpr int FILLWAVE_DO_NOT_ANIMATE = -1;
//constexpr int FILLWAVE_MAX_BONES = 45;
//constexpr int FILLWAVE_MAX_BONES_DEPENDENCIES = 4;
// for #if FILLWAVE_MAX_BONES_DEPENDENCIES == 8 constexpr is not visible

#define FILLWAVE_DO_NOT_ANIMATE -1
#define FILLWAVE_MAX_BONES 45
#define FILLWAVE_MAX_BONES_DEPENDENCIES 4

#endif /* FILLWAVE_ASSETS_H_ */
