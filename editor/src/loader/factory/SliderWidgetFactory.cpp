#include "SliderWidgetFactory.h"
#include <QSlider>

namespace loader {
    namespace factory {
        QWidget *SliderWidgetFactory::create(QVector<std::pair<QString, QString>> &parametersVector,
                                             common::ISceneController *scene) {
            QSlider *slider = new QSlider();
            auto minimum = std::find_if(parametersVector.begin(), parametersVector.end(),
                [](const std::pair<QString, QString> &parameter) { return parameter.first == "minimum"; });
            auto maximum = std::find_if(parametersVector.begin(), parametersVector.end(),
                [](const std::pair<QString, QString> &parameter) { return parameter.first == "maximum"; });
            auto objectName = std::find_if(parametersVector.begin(), parametersVector.end(),
                [](const std::pair<QString, QString> &parameter) { return parameter.first == "objectName"; });
            auto maxWidth = std::find_if(parametersVector.begin(), parametersVector.end(),
                [](const std::pair<QString, QString> &parameter) { return parameter.first == "maxWidth"; });
            auto accessibleName = std::find_if(parametersVector.begin(), parametersVector.end(),
                [](const std::pair<QString, QString> &parameter) { return parameter.first == "accessibleName"; });
            slider->setMinimum(minimum->second.toInt());
            slider->setMaximum(maximum->second.toInt());
            slider->setObjectName(objectName->second);
            slider->setMaximumWidth(maxWidth->second.toInt());
            slider->setAccessibleName(accessibleName->second);
            common::MenuWidgetTranslator *sliderTranslator = new common::MenuWidgetTranslator(slider);
            QObject::connect(slider, &QSlider::sliderReleased, sliderTranslator, &common::MenuWidgetTranslator::update);
            scene->addTranslator(sliderTranslator);
            return slider;
        }
    }
}