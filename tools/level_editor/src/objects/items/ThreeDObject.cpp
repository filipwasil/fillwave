#include "ThreeDObject.h"

namespace objects {

ThreeDObject::ThreeDObject(IItem* parent, QString name, QByteArray id, std::unique_ptr<Model> model)
  : BaseItem(parent, name, id)
  , mModel(std::move(model)) {
  init();
}

void ThreeDObject::init() {
  BaseItem::init();
  //TODO:add to model and scene, node controler should take the model and add him to scene
  //TODO: MVC for inspector, emit signal modelUpdated
}
}