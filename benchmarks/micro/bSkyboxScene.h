#pragma once

#include <flw/Framework.h>
#include <flw/Fillwave.h>

class SkyboxScene : public flw::flf::Scene {
 public:
  SkyboxScene(flw::Engine* engine) {
      auto camera = std::make_unique<flw::flf::CameraPerspective>(glm::vec3(0.0, 0.0, 6.0),
                                                                  glm::quat(),
                                                                  glm::radians(90.0),
                                                                  1.0,
                                                                  0.1,
                                                                  1000.0);

      auto skybox = std::make_unique<flw::flf::Skybox>(
        engine
        , engine->storeTexture3D(
          "125_125_125.color"
          , "125_125_125.color"
          , "125_125_125.color"
          , ""
          , "125_125_125.color"
          , "125_125_125.color"
        )
      );

      setCamera(std::move(camera));

      setSkybox(std::move(skybox));
  }
};
