#pragma once

#include "objects/items/BaseItem.h"

namespace objects {
class ThreeDObject : public BaseItem {
 public:
  ThreeDObject(IItem* parent, QString name, QByteArray id, std::unique_ptr<Model> model);

  void init() override;
 private:
  std::unique_ptr<Model> mModel;
};

}