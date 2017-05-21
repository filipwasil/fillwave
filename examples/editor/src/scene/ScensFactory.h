#pragma once

#include <memory>
#include <functional>
#include <QMap>
#include "AScene.h"

namespace scene {
class ScensFactory {
public:
  ScensFactory(int argc, char **argv);

  std::shared_ptr<scene::AScene> createScen(QString name);

private:
  int mArgc;
  char **mArgv;
  QMap<QString, std::function<std::shared_ptr<scene::AScene>(int, char **)>> mScens;
};
}


