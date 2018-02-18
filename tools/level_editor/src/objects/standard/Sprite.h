#pragma once

#include <QIcon>
#include "objects/ANodeBase.h"

namespace objects {
namespace standard {
class Sprite : public ANodeBase {
 public:
  Sprite(qintptr nodeIde, flw::flf::Model* nodeDataModel, QObject* parent = nullptr);

  ~Sprite() override = default;

  QVector<QStandardItemModel*> getStandardModelForData() override;

  std::string getObjectName();

 private:
  void init();

  QVector<QStandardItemModel*> mTableModelRepresentation;
};
}
}
