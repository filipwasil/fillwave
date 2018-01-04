#include <memory>
#include <QtWidgets/QLabel>
#include <QToolButton>
#include "MainWidget.h"
#include "scene/Renderer.h"
#include "common/windows/basic/NewNode.h"

namespace common {
MainWidget::MainWidget(int argc, char* argv[], QWidget* parent)
  : QMainWindow(parent)
  , mWidgetSplitter(new QSplitter())
  , mCentralWidget(new QWidget(this))
  , mScensTab(new QTabWidget())
  , mRenderer(new Renderer(argc, argv))
  , mArgc(argc)
  , mArgv(argv) {
  mNodeOperations = std::make_unique<MainWindowNodeOperations>(this);
  mFileSystemOperations = std::make_unique<operations::MainWindowFileOperations>(this);
  mNodeController = std::make_unique<common::NodeController>();
  createBarMenu();
  create();
  QObject::connect(mNodeOperations.get(),
                   &MainWindowNodeOperations::addNewNode,
                   mNodeController.get(),
                   &common::NodeController::addNodeToModel);

  QWidget* leftWidget;
  QWidget* rightWidget;
  initMainGui(leftWidget, rightWidget);

  mWidgetSplitter->addWidget(leftWidget);
  mWidgetSplitter->addWidget(mScensTab);
  mWidgetSplitter->addWidget(rightWidget);
  QList<int> sizeList = {
    100,
    mWindowHeight - 200,
    100
  };

  mWidgetSplitter->setSizes(sizeList);
  this->setCentralWidget(mWidgetSplitter);
  resize(mWindowWidth, mWindowHeight);
  auto firstModel = std::make_unique<objects::SceneModel>(0, mRenderer->getScen());

  mNodeController->addSceneModel(std::move(firstModel));
}

void MainWidget::initMainGui(QWidget*& leftWidget, QWidget*& rightWidget) const {
  leftWidget = new QWidget();
  rightWidget = new QWidget();
  QHBoxLayout* vertical = new QHBoxLayout();
  vertical->setDirection(QBoxLayout::LeftToRight);
  QVBoxLayout* layoutEngineWindow = new QVBoxLayout();
  mRenderer->setLayout(layoutEngineWindow);

  QVBoxLayout* verticalLeft = new QVBoxLayout();
  verticalLeft->addLayout(mNodeOperations->createNodeWidget());
  verticalLeft->addLayout(mFileSystemOperations->createFileSystemTree());
  leftWidget->setMinimumWidth(100);
  leftWidget->setLayout(verticalLeft);

  mScensTab->addTab(mRenderer, "empty");

  QVBoxLayout* verticalRight = new QVBoxLayout();
  verticalRight->addLayout(mNodeOperations->createInspectorView());
  verticalRight->addLayout(mNodeOperations->createOther());
  rightWidget->setMinimumWidth(100);
  rightWidget->setLayout(verticalRight);
}

MainWidget::~MainWidget() {
 // TODO: sprawdzić zarządzanie pamięcią
}

void MainWidget::createBarMenu() {
  mFileMenu = menuBar()->addMenu(tr("&File"));
  mEditMenu = menuBar()->addMenu(tr("&Edit"));
  mToolsMenu = menuBar()->addMenu(tr("&Tools"));
  mHelpMenu = menuBar()->addMenu(tr("&Help"));
}

}
