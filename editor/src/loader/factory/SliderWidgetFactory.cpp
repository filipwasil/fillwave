#include "SliderWidgetFactory.h"
#include <QSlider>

namespace loader
{
    namespace factory
    {
        QWidget * SliderWidgetFactory::create(QVector<std::pair<QString, QString>> &parametersVector) {
            QSlider * slider = new QSlider();
            auto minimum = std::find_if(parametersVector.begin(), parametersVector.end(),
                [](const std::pair<QString, QString>& parameter) { return parameter.first == "minimum"; });
            auto maximum = std::find_if(parametersVector.begin(), parametersVector.end(),
                [](const std::pair<QString, QString>& parameter) { return parameter.first == "maximum"; });
            auto accesibleName = std::find_if(parametersVector.begin(), parametersVector.end(),
                [](const std::pair<QString, QString>& parameter) { return parameter.first == "accesibleName"; });
            auto maxWidth = std::find_if(parametersVector.begin(), parametersVector.end(),
                [](const std::pair<QString, QString>& parameter){ return parameter.first == "maxWidth"; });
            slider->setMinimum(minimum->second.toInt());
            slider->setMaximum(maximum->second.toInt());
            slider->setAccessibleName(accesibleName->second);
            slider->setMaximumWidth(maxWidth->second.toInt());
            return slider;
        }
    }
}