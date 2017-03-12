#pragma once
#include "IMenuWidgetFactory.h"

namespace loader
{
    namespace factory
    {
        class SliderWidgetFactory: public IMenuWidgetFactory
        {
        public:
            QWidget *create(QVector<std::pair<QString, QString>> &parametersVector, common::ISceneController *scene);
        };
    }
}

