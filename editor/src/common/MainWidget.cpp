#include "MainWidget.h"
#include "scene/Renderer.h"
#include <memory>

namespace common {
    MainWidget::MainWidget(int argc, char *argv[], QWidget *parent) :
        QMainWindow(parent),
        mCentralWidget(new QWidget(this)),
        mRenderer(new Renderer(argc, argv)) {
        createBarMenuActions();
        createBarMenuCategories();

        QVBoxLayout *horizontal = new QVBoxLayout();
        horizontal->setDirection(QBoxLayout::LeftToRight);

        QVBoxLayout *layoutEngineWindow = new QVBoxLayout();
        loader::LoadMenu defaultMenu;
        mSceneController = new common::SceneController(mRenderer);
        auto mainMenu = defaultMenu.createDefaultMainMenu(mSceneController);
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


}
