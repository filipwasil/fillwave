#include <QLineEdit>
#include "LineEditWidgetFactory.h"
#include "common/MenuWidgetTranslator.h"

namespace loader {
    namespace factory {

        QWidget *LineEditWidgetFactory::create(QVector<std::pair<QString, QString>> &parametersVector,
                                               common::ISceneController *scene) {
            auto objectName = std::find_if(parametersVector.begin(), parametersVector.end(),
                [](const std::pair<QString, QString> &parameter) { return parameter.first == "objectName"; });
            auto text = std::find_if(parametersVector.begin(), parametersVector.end(),
                [](const std::pair<QString, QString> &parameter) { return parameter.first == "defaultText"; });
            auto maxWidth = std::find_if(parametersVector.begin(), parametersVector.end(),
                [](const std::pair<QString, QString> &parameter) { return parameter.first == "maxWidth"; });
            auto accessibleName = std::find_if(parametersVector.begin(), parametersVector.end(),
                [](const std::pair<QString, QString> &parameter) { return parameter.first == "accessibleName"; });
            QLineEdit *textArea = new QLineEdit();
            textArea->setObjectName(objectName->second);
            textArea->setText(text->second);
            textArea->setMaximumWidth(maxWidth->second.toInt());
            textArea->setAccessibleName(accessibleName->second);
            common::MenuWidgetTranslator *textTranslator = new common::MenuWidgetTranslator(textArea);
            QObject::connect(textArea, &QLineEdit::returnPressed, textTranslator,
                &common::MenuWidgetTranslator::update);
            scene->addTranslator(textTranslator);
            return textArea;
        }
    }
}