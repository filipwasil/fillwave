//
// Created by filip on 25.04.16.
//

#include "MainWidget.h"
#include "scene/Renderer.h"
#include "loader/XmlLoader.h"
#include <QLabel>
#include <QList>
#include <QMessageBox>


namespace common {
    MainWidget::MainWidget(int argc, char *argv[], QWidget *parent) :
            QMainWindow(parent),
            mCentralWidget(new QWidget(this)),
            mRenderer(new Renderer(argc, argv))
    {
        createBarMenuActions();
        createBarMenuCategories();

        QVBoxLayout *horizontal = new QVBoxLayout();
        horizontal->setDirection(QBoxLayout::LeftToRight);

        QVBoxLayout *layoutEngineWindow = new QVBoxLayout();

        auto mainMenu = createMainMenu();
        horizontal->addLayout(mainMenu);

        mRenderer->setLayout(layoutEngineWindow);
        horizontal->addWidget(mRenderer);

        mCentralWidget->setLayout(horizontal);
        this->setCentralWidget(mCentralWidget);
        resize(800, 400);
    }

    MainWidget::~MainWidget() {

    }

    void MainWidget::createBarMenuActions() {
        auto helloWorldAction = new QAction(tr("Hello World"), this);

        QList<QAction *> scensActionList;
        scensActionList.append(helloWorldAction);
        mActionsListMap["Scens"] = scensActionList;
    }

    void MainWidget::createBarMenuCategories() {
        mMenuBar = this->menuBar();
        auto scens = mMenuBar->addMenu("Scens");

        if (!mActionsListMap.contains("Scens")) {
            return;
        }
        auto ScensActionList = mActionsListMap["Scens"];
        for (auto action : ScensActionList) {
            scens->addAction(action);
        }
    }

    QVBoxLayout* MainWidget::createMainMenu() {
        loader::XmlLoader *loadMenuEntries = new loader::XmlLoader();
        QList<QWidget *> menuWidgets;
        menuWidgets = loadMenuEntries->load(HELLO_WORLD_MENU_FILE);
        if(menuWidgets.isEmpty()) {
            QMessageBox msgBox;
            msgBox.setText("Fail to load HelloWorld xml file!");
            msgBox.exec();
            return nullptr;
        }
        QVBoxLayout *vbox = new QVBoxLayout();
        for(auto mWidget : menuWidgets) {
            QLabel* label = new QLabel(mWidget->accessibleName());
            vbox->addWidget(label);
            vbox->addWidget(mWidget);
        }
        vbox->setAlignment(Qt::AlignTop);
        return vbox;
    }
}
