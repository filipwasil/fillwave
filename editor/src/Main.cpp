#include <QApplication>
#include "scene/Renderer.h"
#include "common/MainWidget.h"
#include <QLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    common::MainWidget w(argc, argv);
    w.show();
    return app.exec();
}
