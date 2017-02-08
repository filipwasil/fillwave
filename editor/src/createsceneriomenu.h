#ifndef CREATESCENERIOMENU_H
#define CREATESCENERIOMENU_H
#include <QVector>
#include "xmlreader.h"
#include "createmenuwidgets.h"

namespace scenerio
{
class CreateScenerioMenu
{
public:
    CreateScenerioMenu();
    QList<QWidget*> create(QString path);
private:
    void loadFile(QString path);
};
}
#endif // CREATESCENERIOMENU_H
