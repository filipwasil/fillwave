#include "DialWidgetFactory.h"
#include "QDial"

namespace loader
{
    namespace factory
    {

        QWidget *DialWidgetFactory::create(QVector<std::pair<QString, QString>> &parametersVector) {
            QDial* slider = new QDial();
            QString fieldName = "minimum";
            auto parameterName = [&fieldName](const std::pair<QString, QString>& parameter)
                { return parameter.first == fieldName; };
            auto minimum = std::find_if(parametersVector.begin(), parametersVector.end(), parameterName);

            fieldName = "maximum";
            auto maximum = std::find_if(parametersVector.begin(), parametersVector.end(), parameterName);

            slider->setMinimum(minimum->second.toInt());
            slider->setMaximum(maximum->second.toInt());
            return slider;
        }
    }
}
