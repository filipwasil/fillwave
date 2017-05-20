#include <QPushButton>
#include "common/translators/MenuWidgetTranslatorButtonColor.h"
#include "PushButtonWidgetFactory.h"
namespace loader {
namespace factory {
QWidget *PushButtonWidgetFactory::create(QVector<std::pair<QString, QString>> &parametersVector,
    std::shared_ptr<common::ISceneController> scene) {
  auto objectName = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "objectName"; });
  auto text = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "defaultText"; });
  auto maxWidth = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "maxWidth"; });
  auto accessibleName = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "accessibleName"; });
  auto translatorType = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "translatorType"; });
  auto defaultValue = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "defaultValue"; });
  QPushButton *button = new QPushButton(text->second);
  button->setObjectName(objectName->second);
  button->setMaximumWidth(maxWidth->second.toInt());
  button->setAccessibleName(accessibleName->second);
  if (!mTranslatorTypes.contains(translatorType->second)) {
    return nullptr;
  }
  common::translators::IMenuWidgetTranslator *buttonTranslator =
      mTranslatorTypes["ColorDialog"](button, defaultValue->second);
  QObject::connect(button, &QPushButton::clicked, buttonTranslator, &common::translators::IMenuWidgetTranslator::update);
  scene->addTranslator(buttonTranslator);
  return button;
}

PushButtonWidgetFactory::PushButtonWidgetFactory() {
  mTranslatorTypes["ColorDialog"] = [](QWidget* widget, QString value) { return new
      common::translators::MenuWidgetTranslatorButtonColor(widget, value);};
}
}
}