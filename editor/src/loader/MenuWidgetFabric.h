#ifndef MENUWIDGETFABRIC_H
#define MENUWIDGETFABRIC_H

#include <QWidget>

namespace loader
{
    class MenuWidgetFabric
    {
    public:
        QWidget * createWidget(QString typeName, QVector<std::pair<QString, QString>> &parametersVector);
    };

}

#endif //FILLWAVE_QT_EXAMPLE_MENUWIDGETFABRIC_H
