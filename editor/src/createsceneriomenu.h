#ifndef CREATESCENERIOMENU_H
#define CREATESCENERIOMENU_H
#include <QVector>
#include "xmlreader.h"
#include "createmenuwidgets.h"

namespace sceneriocreation
{
class CreateScenerioMenu
{
public:
    CreateScenerioMenu();
    QVector<QWidget*> create(QString path);
private:
    void loadFile(QString path);
};
}
#endif // CREATESCENERIOMENU_H
