#include <QLineEdit>
#include <memory>
#include "LineEditWidgetFactory.h"
#include "common/translators/MenuWidgetTranslatorLineEdit.h"

namespace loader {
namespace factory {

QWidget *LineEditWidgetFactory::create(QVector<std::pair<QString, QString>> &parametersVector,
    std::shared_ptr<common::ISceneController> scene) {
  auto objectName = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "objectName"; });
  auto text = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "defaultText"; });
  auto maxWidth = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "maxWidth"; });
  auto accessibleName = std::find_if(parametersVector.begin(), parametersVector.end(),
      [](const std::pair <QString, QString> &parameter) { return parameter.first == "accessibleName"; });
  QLineEdit *textArea = new QLineEdit();
  textArea->setObjectName(objectName->second);
  textArea->setText(text->second);
  textArea->setMaximumWidth(maxWidth->second.toInt());
  textArea->setAccessibleName(accessibleName->second);
  common::translators::IMenuWidgetTranslator *textTranslator = new common::translators::MenuWidgetTranslatorLineEdit(textArea);
  QObject::connect(textArea, &QLineEdit::returnPressed, textTranslator, &common::translators::IMenuWidgetTranslator::update);
  scene->addTranslator(textTranslator);
  return textArea;
}
}
}