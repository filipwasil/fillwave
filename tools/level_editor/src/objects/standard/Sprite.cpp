#include "Sprite.h"

namespace objects {
namespace standard {
Sprite::Sprite(qintptr nodeIde, flw::flf::Model* nodeDataModel, QObject* parent)
  : ANodeBase(parent, nodeDataModel, nodeIde) {
  init();
}

QVector<QStandardItemModel*> Sprite::getStandardModelForData() {
  return mTableModelRepresentation;
}

std::string Sprite::getObjectName() {
  return "TestSpriteName"; // TODO: Potrzebna funkcja w silniku zwracajaca nazwę.
}

void Sprite::init() {
  if (!mNodeDataModel)
  {
    return;
  }
  QStandardItemModel* positionModel = new QStandardItemModel(this);
  QList<QStandardItem*> positionNameColumn;
  QList<QStandardItem*> positionValuesColumn;
  positionNameColumn.append(new QStandardItem("X"));
  positionNameColumn.append(new QStandardItem("Y"));
  positionNameColumn.append(new QStandardItem("Z"));
  positionNameColumn.append(new QStandardItem("Scale X"));
  positionNameColumn.append(new QStandardItem("Scale Y"));
  positionNameColumn.append(new QStandardItem("Scale Z"));
  glm::vec3 position = mNodeDataModel->getTranslation();
  positionValuesColumn.append(new QStandardItem(position[0]));
  positionValuesColumn.append(new QStandardItem(position[1]));
  positionValuesColumn.append(new QStandardItem(position[2]));
  glm::vec3 scale = mNodeDataModel->getScale();
  positionValuesColumn.append(new QStandardItem(scale[0]));
  positionValuesColumn.append(new QStandardItem(scale[1]));
  positionValuesColumn.append(new QStandardItem(scale[2]));
  positionModel->insertColumn(0, positionNameColumn);
  positionModel->insertColumn(1, positionValuesColumn);

  mTableModelRepresentation.push_back(positionModel);
}

void Sprite::AddObjectToScene(std::shared_ptr<scene::AScene> mSceneView) {

}


}
}
