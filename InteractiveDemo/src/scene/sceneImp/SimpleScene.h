#pragma once
#include <fillwave/Fillwave.h>
#include "scene/AScene.h"
namespace scene {
class SimpleScene : public AScene {
Q_OBJECT
  Q_PROPERTY(QMap<QString, QVariant> sceneParameter
                 READ
                 getParameters
                 WRITE
                 setParameters)
  void setDefaultParameters(const QVector<std::pair<QString, QString>> &param) override;

public:
  SimpleScene(int argc, char **argv);

  virtual ~SimpleScene();

  void init() override;

  void perform() override;

private:
  int mArgc;
  char **mArgv;
};
}



