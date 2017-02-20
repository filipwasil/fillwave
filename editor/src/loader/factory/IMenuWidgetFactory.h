#ifndef IMENUWIDGETFACTORY_H
#define IMENUWIDGETFACTORY_H

#include <QWidget>
#include <QVector>

namespace loader
{
namespace factory
{
    class IMenuWidgetFactory
    {
    public:
        virtual QWidget * create(QVector<std::pair<QString, QString>> &parametersVector) = 0;
    };
}
}


#endif //IMENUWIDGETFACTORY_H
