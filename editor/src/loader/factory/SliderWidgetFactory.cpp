#include "SliderWidgetFactory.h"
#include <QSlider>

namespace loader
{
    namespace factory
    {
        QWidget * SliderWidgetFactory::create(QVector<std::pair<QString, QString>> &parametersVector) {
            QSlider * slider = new QSlider();
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