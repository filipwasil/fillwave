#include <memory>
#include <QtWidgets/QLabel>
#include <QDockWidget>
#include <QToolButton>
#include <QListWidget>
#include "MainWidget.h"
#include "scene/Renderer.h"

namespace common {
MainWidget::MainWidget(int argc, char* argv[], QWidget* parent)
  : QMainWindow(parent)
  , mCentralWidget(new QWidget(this))
  , mScensTab(new QTabWidget(this))
  , mRenderer(new Renderer(argc, argv))
  , mArgc(argc)
  , mArgv(argv) {
  mNodeOperations = std::make_unique<MainWindowNodeOperations>(this);
  mFileSystemOperations = std::make_unique<operations::MainWindowFileOperations>(this);
  createBarMenu();
  create();
  initMainGui();

  mScensTab->addTab(mRenderer, "Empty");
  QVBoxLayout* tabLayout = new QVBoxLayout();
  tabLayout->addWidget(mScensTab);
  mCentralWidget->setLayout(tabLayout);
  this->setCentralWidget(mCentralWidget);
  resize(mWindowWidth, mWindowHeight);
}

MainWidget::~MainWidget() {
  // TODO: check memory
}

void MainWidget::initMainGui() {
  auto nodeWindow = new QWidget();
  auto fileWindow = new QWidget();
  auto inspectorWindow = new QWidget();
  auto objectPropertiesWindow = new QWidget();

  QVBoxLayout* nodeLayout = new QVBoxLayout();
  nodeLayout->addLayout(mNodeOperations->createNodeLayout(nodeWindow));
  nodeWindow->setLayout(nodeLayout);

  QVBoxLayout* fileLayout = new QVBoxLayout();
  fileLayout->addLayout(mFileSystemOperations->createFileSystemTree(fileWindow));
  fileWindow->setLayout(fileLayout);

  QVBoxLayout* inspectorLayout = new QVBoxLayout();
  inspectorLayout->addLayout(mNodeOperations->createInspectorViewLayout(inspectorWindow));
  inspectorWindow->setLayout(inspectorLayout);

  QVBoxLayout* propertiesLayout = new QVBoxLayout();
  propertiesLayout->addLayout(mNodeOperations->createObjectPropertiesLayout(objectPropertiesWindow));
  objectPropertiesWindow->setLayout(propertiesLayout);

  QDockWidget *dock = new QDockWidget(tr("NodeArea"), this);
  dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  dock->setWidget(nodeWindow);
  addDockWidget(Qt::LeftDockWidgetArea, dock, Qt::Horizontal);

  dock = new QDockWidget(tr("FileArea"), this);
  dock->setWidget(fileWindow);
  addDockWidget(Qt::LeftDockWidgetArea, dock, Qt::Horizontal);

  dock = new QDockWidget(tr("InspectorArea"), this);
  dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  dock->setWidget(inspectorWindow);
  addDockWidget(Qt::RightDockWidgetArea, dock, Qt::Horizontal);

  dock = new QDockWidget(tr("PropertiesArea"), this);
  dock->setWidget(objectPropertiesWindow);
  addDockWidget(Qt::RightDockWidgetArea, dock, Qt::Horizontal);
}

void MainWidget::createBarMenu() {
  mFileMenu = menuBar()->addMenu(tr("&File"));
  mEditMenu = menuBar()->addMenu(tr("&Edit"));
  mToolsMenu = menuBar()->addMenu(tr("&Tools"));
  mHelpMenu = menuBar()->addMenu(tr("&Help"));
}

}
