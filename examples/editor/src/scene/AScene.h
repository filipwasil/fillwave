#pragma once

#include <utility>
#include <memory>
#include <QString>
#include <QMap>
#include <QVariant>
#include <QVector>
#include <QObject>
#include <fillwave/Fillwave.h>
#include "scene/callbacks/IEventHandler.h"
#include "scene/callbacks/Callbacks.h"
#include <scene/callbacks/StandardKeyboardEventHandler.h>
#include <scene/callbacks/StandardMouseEventHandler.h>

namespace scene {
class AScene : public QObject {

 public:
  AScene(int argc, char* const* argv, QMap<QString, QVariant> parametersMap)
    : mSceneParameters(parametersMap) {
    if (argv != nullptr) {
      mEngine = std::make_shared<flw::Engine>(argc, argv);
    }
  }

  virtual ~AScene() = default;

  virtual void init() = 0;

  virtual void perform() = 0;

  QMap<QString, QVariant> getParameters() {
    return mSceneParameters;
  };

  virtual void setParameters(QMap<QString, QVariant> parameters) {
    if (!mSceneParameters.contains(parameters.firstKey())) {
      return;
    }
    mSceneParameters[parameters.firstKey()] = parameters.first();
    perform();
  };

  std::shared_ptr<flw::Engine> getEngine() {
    return mEngine;
  };

  bool eventFilter(QObject* watched, QEvent* event) override {
    if (!mEventsHandler.empty()) {
      for (auto& mEvent : mEventsHandler) {
        mEvent->handle(event);
      }
    }
    return QObject::eventFilter(watched, event);
  }

  void prepareStandardCallbacks() {
    mTimeCallback = std::make_unique<flw::flf::TimeStopCallback>(mEngine.get());
    mCameraCallback = std::make_unique<flw::flf::MoveCameraCallback>(mEngine.get(), 0.1);
    mSecondCameraCallback = std::make_unique<flw::flf::FollowCustomCursorCallback>(mEngine.get());
    std::function<void(const flw::flf::Event&)> timeFuncHandler = std::bind(&flw::flf::TimeStopCallback::perform,
                                                                            &(*mTimeCallback),
                                                                            std::placeholders::_1);
    std::function<void(const flw::flf::Event&)> cameraFuncHandler = std::bind(&flw::flf::MoveCameraCallback::perform,
                                                                              &(*mCameraCallback),
                                                                              std::placeholders::_1);
    std::function<void(const flw::flf::Event&)> secondCameraFuncHandler = std::bind(&flw::flf::FollowCustomCursorCallback::perform,
                                                                                    &(*mSecondCameraCallback),
                                                                                    std::placeholders::_1);
    mEngine->attachHandler(std::move(timeFuncHandler), flw::flf::EEventType::key);
    mEngine->attachHandler(std::move(cameraFuncHandler), flw::flf::EEventType::key);
    mEngine->attachHandler(std::move(secondCameraFuncHandler), flw::flf::EEventType::cursorPosition);

    mEventsHandler.push_back(std::make_unique<callbacks::StandardKeyboardEventHandler>(mEngine));
    mEventsHandler.push_back(std::make_unique<callbacks::StandardMouseEventHandler>(mEngine));
  }

 protected:
  std::shared_ptr<flw::Engine> mEngine;
  QMap<QString, QVariant> mSceneParameters;
  std::vector<std::unique_ptr<scene::callbacks::IEventHandler>> mEventsHandler;
  std::unique_ptr<flw::flf::TimeStopCallback> mTimeCallback;
  std::unique_ptr<flw::flf::MoveCameraCallback> mCameraCallback;
  std::unique_ptr<flw::flf::FollowCustomCursorCallback> mSecondCameraCallback;
};
}
