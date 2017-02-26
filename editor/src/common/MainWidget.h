//
// Created by filip on 25.04.16.
//

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QAction>

class QPushButton;

class Renderer;

class Panel;

namespace common {
    class MainWidget : public QMainWindow {
    Q_OBJECT

    public:
        MainWidget(int argc, char *argv[], QWidget *parent = 0);

        virtual ~MainWidget();

    private:
        void createBarMenuActions();

        void createMenuCategories();

        QWidget *mCentralWidget;
        Renderer *mRenderer;
        QMenuBar *mMenuBar;
        QMap<QString, QList<QAction *>> mActionsListMap;
    };

}

#endif //MAINWIDGET_H
