#ifndef FILLWAVE_QT_EXAMPLE_MENUWIDGETFABRIC_H
#define FILLWAVE_QT_EXAMPLE_MENUWIDGETFABRIC_H

#include <QList>
#include <QWidget>

namespace loader
{
    class MenuWidgetFabric
    {
    public:
        QList<QWidget *> createWidget(QString typeName, QVector<std::pair<QString, QString>> &parametersVector);
    };

}

#endif //FILLWAVE_QT_EXAMPLE_MENUWIDGETFABRIC_H
