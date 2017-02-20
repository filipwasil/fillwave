#include "DialWidgetFactory.h"
#include "QDial"

namespace loader
{
    namespace factory
    {

        QWidget *DialWidgetFactory::create(QVector<std::pair<QString, QString>> &parametersVector)
        {
            QDial * slider = new QDial();
            auto minimum = std::find_if(parametersVector.begin(), parametersVector.end(),
                [](const std::pair<QString, QString>& parameter){ return parameter.first == "minimum"; });
            auto maximum = std::find_if(parametersVector.begin(), parametersVector.end(),
                [](const std::pair<QString, QString>& parameter){ return parameter.first == "maximum"; });
            slider->setMinimum(minimum->second.toInt());
            slider->setMaximum(maximum->second.toInt());
            return slider;
        }
    }
}
