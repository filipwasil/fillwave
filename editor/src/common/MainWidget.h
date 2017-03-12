#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>
#include "loader/LoadMenu.h"
#include "common/SceneController.h"

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

        void createBarMenuCategories();

        QWidget *mCentralWidget;
        Renderer *mRenderer;
        QMenuBar *mMenuBar;
        QMap<QString, QList<QAction *>> mActionsListMap;
        SceneController *mSceneController;
    };

}

#endif //MAINWIDGET_H
