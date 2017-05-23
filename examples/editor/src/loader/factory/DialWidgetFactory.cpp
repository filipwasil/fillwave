#include <memory>
#include "DialWidgetFactory.h"
#include "QDial"

namespace loader {
namespace factory {

QWidget *
DialWidgetFactory::create(QVector<std::pair<QString, QString>> &parametersVector,
    std::shared_ptr<common::ISceneController> scene) {
  QDial *slider = new QDial();
  auto minimum = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "minimum"; });
  auto maximum = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "maximum"; });
  auto objectName = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "objectName"; });
  auto maxWidth = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "maxWidth"; });
  auto accessibleName = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "accessibleName"; });
  auto defaultValue = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "defaultValue"; });
  slider->setMinimum(minimum->second.toInt());
  slider->setMaximum(maximum->second.toInt());
  slider->setObjectName(objectName->second);
  slider->setMaximumWidth(maxWidth->second.toInt());
  slider->setAccessibleName(accessibleName->second);
  slider->setValue(defaultValue->second.toInt());
  common::translators::MenuWidgetTranslatorStandardValues *sliderTranslator = new
      common::translators::MenuWidgetTranslatorStandardValues(slider);
  QObject::connect(slider, &QDial::sliderReleased, sliderTranslator, &common::translators::MenuWidgetTranslatorStandardValues::update);
  scene->addTranslator(sliderTranslator);
  return slider;
}
}
}
