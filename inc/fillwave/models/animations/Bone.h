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

#include <fillwave/models/animations/Hinge.h>
#include <fillwave/loaders/ModelLoaderTraits.h>

namespace flw {
namespace flf {
class Bone;
}

typedef std::unique_ptr<flf::Bone> puBone;

namespace flf {

/*! \class Bone
 * \brief Hinge used by Animator to populate bone transformations.
 */

class Bone final : public Hinge {
public:
  Bone(aiBone *assimpBone);

  ~Bone() override = default;

  std::string getName() const;

  glm::mat4 getOffsetMatrix() const;

  glm::mat4 getGlobalOffsetMatrix() const;

  void setName(std::string name);

  void setOffsetMatrix(glm::mat4 m);

  void setGlobalOffsetMatrix(glm::mat4 m);

  void log() const override;

private:
  std::string mName;
  glm::mat4 mOffsetMatrix;
  glm::mat4 mGlobalOffsetMatrix;
};

} /* flf */
} /* flw */
