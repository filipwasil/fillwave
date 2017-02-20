#include "LineEditWidgetFactory.h"
#include <QLineEdit>

namespace loader
{
    namespace factory
    {

        QWidget *LineEditWidgetFactory::create(QVector<std::pair<QString, QString>> &parametersVector) {
            auto text = std::find_if(parametersVector.begin(), parametersVector.end(),
                [](const std::pair<QString, QString>& parameter){ return parameter.first == "text"; });
            QLineEdit * textArea = new QLineEdit(text->second);
            return textArea;
        }
    }
}