//
// Created by filip on 15.09.17.
//

#include "Cradle.h"
#include <fillwave/Framework.h>
#include <fillwave/common/Macros.h>
#include <memory>

using namespace std;
using namespace flw;
using namespace flw::flf;

Cradle::Cradle(flw::Engine* engine) {
  //create ground
  auto ground = make_unique <Model> (
      engine
      , ProgramLoader(engine).getProgram(EProgram::basic)
      , "models/kolyska.dae"
      , "128_128_128.color"
      , "128_128_128.color"
      , "128_128_128.color"
  );
  ground->addEffect(make_shared<TextureOnly>());
  ground->scaleTo(0.005);
  ground->rotateByX(glm::radians(180.0f));
  ground->rotateByY(glm::radians(180.0f));
  ground->rotateByZ(glm::radians(45.0f));
  engine->getCurrentScene()->attach(std::move(ground));

  auto railsOuter = make_unique <Model> (
      engine
      , ProgramLoader(engine).getProgram(EProgram::basic)
      , "models/kolyska_1.dae"
      , "0_128_128.color"
      , "0_128_128.color"
      , "0_128_128.color"
  );

  // railsOuter
  railsOuter->addEffect(make_shared<TextureOnly>());
  railsOuter->scaleTo(0.0045);
  railsOuter->rotateByX(glm::radians(180.0f));
  railsOuter->rotateByY(glm::radians(180.0f));
  railsOuter->rotateByZ(glm::radians(45.0f));

  railsOuter->rotateBy(2.0, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0), BounceEaseOut);
  railsOuter->rotateBy(2.0, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0), BounceEaseOut);
  railsOuter->rotateBy(2.0, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0), BounceEaseOut);
  railsOuter->rotateBy(2.0, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0), BounceEaseOut);
  railsOuter->loop(5000);

  auto railsInner = make_unique <Model> (
      engine
      , ProgramLoader(engine).getProgram(EProgram::basic)
      , "models/kolyska_1.dae"
      , "0_128_0.color"
      , "0_128_0.color"
      , "0_128_0.color"
  );

  railsInner->addEffect(make_shared<TextureOnly>());
  railsInner->rotateByX(glm::radians(90.0f));
  railsInner->rotateByZ(glm::radians(90.0f));
  railsInner->rotateBy(1.5, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0), BounceEaseOut);
  railsInner->rotateBy(2.5, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0), BounceEaseOut);
  railsInner->rotateBy(3.5, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0), BounceEaseOut);
  railsInner->rotateBy(0.5, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0), BounceEaseOut);
  railsInner->loop(5000);

  railsOuter->attach(std::move(railsInner));

  engine->getCurrentScene()->attach(std::move(railsOuter));

  mAccelerationF =
      engine->storeText(
          "V:", "fonts/bridgenorth", glm::vec2(-0.95, 0.95), 100.0, glm::vec4(1.0, 1.0, 1.0, 1.0), ETextEffect::eBold);
  mAccelerationH =
      engine->storeText(
          "H:", "fonts/bridgenorth", glm::vec2(-0.95, 0.85), 100.0, glm::vec4(1.0, 1.0, 1.0, 1.0), ETextEffect::eBold);
  mAccelerationV =
      engine->storeText(
          "F:", "fonts/bridgenorth", glm::vec2(-0.95, 0.75), 100.0, glm::vec4(1.0, 1.0, 1.0, 1.0), ETextEffect::eBold);

//  engine->attachHandler([] (flf::Event& event), eEventType::key) {
//  if (event.mData.mKey == GLFW_KEY_T && event.mData.mKey == GLFW_PRESS) {
//    if (mTimeOn) {
//      mTimeOn = false;
//      mEngine->configTime(0.0);
//    } else {
//      mTimeOn = true;
//      mEngine->configTime(1.0);
//    }
//  }
//  });
}

void Cradle::setAcceleration(float vertical, float horizontal, float frontal) {
  char buf[3][128] = {'\0'};
  sprintf(buf[0], "V: %f", static_cast<double>(vertical));
  sprintf(buf[1], "H: %f", static_cast<double>(horizontal));
  sprintf(buf[2], "F: %f", static_cast<double>(frontal));
  mAccelerationF->editString(buf[0]);
  mAccelerationH->editString(buf[1]);
  mAccelerationV->editString(buf[2]);
}