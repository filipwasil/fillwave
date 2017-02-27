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
    class MainWidget : public QMainWindow {
    Q_OBJECT

    public:
        MainWidget(int argc, char *argv[], QWidget *parent = 0);

        virtual ~MainWidget();

    private:
        void createBarMenuActions();

        void createBarMenuCategories();

        QVBoxLayout* createMainMenu();

        QList<QWidget *> getMenuWidgetList() const;

        QVBoxLayout *getMainMenuVBoxLayout(const QList<QWidget *> &menuWidgets);

        const QString mDefaultScenerioMenu;
        QWidget *mCentralWidget;
        Renderer *mRenderer;
        QMenuBar *mMenuBar;
        QMap<QString, QList<QAction *>> mActionsListMap;


    };

}

#endif //MAINWIDGET_H
