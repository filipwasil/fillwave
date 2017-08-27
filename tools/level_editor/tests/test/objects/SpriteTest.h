#pragma once
#include <gtest/gtest.h>
#include <fillwave/Framework.h>
#include <fillwave/Fillwave.h>
#include "objects/standard/Sprite.h"

class SpriteTest : public testing::Test {
 public:
  SpriteTest() : sut_(0, nullptr) {
   /* std::string str = "/";
    auto engine = std::make_shared<flw::Engine>(1, nullptr);
    flw::puModel ballModel1 = std::make_unique<flw::flf::Model>(nullptr, nullptr,
                                                    "meshes/sphere.obj");*/

  }

  virtual void SetUp() override {
    //sut_ = {0, nullptr};
  }

  virtual void TearDown() override {
  }
 protected:
  objects::standard::Sprite sut_;
};



