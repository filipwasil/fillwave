#ifndef SLIDERWIDGETFACTORY_H
#define SLIDERWIDGETFACTORY_H

#include "IMenuWidgetFactory.h"

namespace loader
{
    namespace factory
    {
        class SliderWidgetFactory: public IMenuWidgetFactory
        {
        public:
            QWidget * create(QVector<std::pair<QString, QString>> &parametersVector);
        };
    }
}



#endif //SLIDERWIDGETFACTORY_H
