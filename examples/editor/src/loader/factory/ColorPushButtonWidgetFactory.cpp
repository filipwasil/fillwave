#include <QPushButton>
#include <QHash>
#include "common/translators/MenuWidgetTranslatorButtonColor.h"
#include "ColorPushButtonWidgetFactory.h"
namespace loader {
namespace factory {
QWidget *ColorPushButtonWidgetFactory::create(QVector<std::pair<QString, QString>> &parametersVector,
    std::shared_ptr<common::ISceneController> scene) {
  auto objectName = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "objectName"; });
  auto text = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "defaultText"; });
  auto maxWidth = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "maxWidth"; });
  auto accessibleName = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "accessibleName"; });
  auto defaultValueRed = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "defaultRed"; });
  auto defaultValueGreen = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "defaultGreen"; });
  auto defaultValueBlue = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "defaultBlue"; });
  auto defaultValueAlpha = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "defaultAlpha"; });
  QPushButton *button = new QPushButton(text->second);
  button->setObjectName(objectName->second);
  button->setMaximumWidth(maxWidth->second.toInt());
  button->setAccessibleName(accessibleName->second);
  QHash<QString, float> defaultValues;
  defaultValues["Red"] = defaultValueRed->second.toFloat();
  defaultValues["Green"] = defaultValueGreen->second.toFloat();
  defaultValues["Blue"] = defaultValueBlue->second.toFloat();
  defaultValues["Alpha"] = defaultValueAlpha->second.toFloat();
  common::translators::IMenuWidgetTranslator *buttonTranslator = new
      common::translators::MenuWidgetTranslatorButtonColor(button, defaultValues);
  QObject::connect(button, &QPushButton::clicked, buttonTranslator, &common::translators::IMenuWidgetTranslator::update);
  scene->addTranslator(buttonTranslator);
  return button;
}
}
}