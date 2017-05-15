#pragma once

#include <memory>
#include <functional>
#include <QHash>
#include "AScene.h"

namespace scene {
class ScensFactory {
public:
  ScensFactory(int argc, char **argv);

  std::shared_ptr<scene::AScene> createScen(QString name);

private:
  int mArgc;
  char **mArgv;
  QHash<QString, std::function<std::shared_ptr<scene::AScene>(int, char **)>> mScens;
};
}


