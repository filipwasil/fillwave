#include <QApplication>
#include "Renderer.h"
#include "MainWidget.h"
#include <QLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWidget w(argc, argv);
    w.show();
    return app.exec();
}
