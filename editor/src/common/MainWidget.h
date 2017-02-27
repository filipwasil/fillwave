//
// Created by filip on 25.04.16.
//

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>

class QPushButton;

class Renderer;

class Panel;

namespace common {
#define HELLO_WORLD_MENU_FILE "assets/SceneriosMenu/HelloWorld.xml"

    class MainWidget : public QMainWindow {
    Q_OBJECT

    public:
        MainWidget(int argc, char *argv[], QWidget *parent = 0);

        virtual ~MainWidget();

    private:
        void createBarMenuActions();

        void createBarMenuCategories();

        QVBoxLayout* createMainMenu();

        QWidget *mCentralWidget;
        Renderer *mRenderer;
        QMenuBar *mMenuBar;
        QMap<QString, QList<QAction *>> mActionsListMap;
    };

}

#endif //MAINWIDGET_H
