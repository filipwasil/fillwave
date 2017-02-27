#include "LineEditWidgetFactory.h"
#include <QLineEdit>

namespace loader
{
    namespace factory
    {

        QWidget *LineEditWidgetFactory::create(QVector<std::pair<QString, QString>> &parametersVector) {
            auto accesibleName = std::find_if(parametersVector.begin(), parametersVector.end(),
                [](const std::pair<QString, QString>& parameter){ return parameter.first == "accesibleName"; });
            auto text = std::find_if(parametersVector.begin(), parametersVector.end(),
                [](const std::pair<QString, QString>& parameter){ return parameter.first == "defaultText"; });
            auto maxWidth = std::find_if(parametersVector.begin(), parametersVector.end(),
                [](const std::pair<QString, QString>& parameter){ return parameter.first == "maxWidth"; });

            QLineEdit * textArea = new QLineEdit();
            textArea->setAccessibleName(accesibleName->second);
            textArea->setText(text->second);
            textArea->setMaximumWidth(maxWidth->second.toInt());
            return textArea;
        }
    }
}