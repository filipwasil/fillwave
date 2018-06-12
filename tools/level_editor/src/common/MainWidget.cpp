#include <memory>
#include <QAction>
#include <QtWidgets/QLabel>
#include <QToolButton>
#include <QListWidget>
#include "MainWidget.h"
#include "scene/Renderer.h"

namespace common {
MainWidget::MainWidget(int argc, char* argv[], QWidget* parent)
  : QMainWindow(parent)
  , mCentralWidget(new QWidget(this))
  , mScenesTab(new QTabWidget(this))
  , mRenderer(new Renderer(argc, argv))
  , mArgc(argc)
  , mArgv(argv) {
  createBarMenu();
  create();
  initMainGui();

  mScenesTab->addTab(mRenderer, "Empty");
  auto tabLayout = new QVBoxLayout();
  tabLayout->addWidget(mScenesTab);
  mCentralWidget->setLayout(tabLayout);
  this->setCentralWidget(mCentralWidget);
  resize(mWindowWidth, mWindowHeight);
}

MainWidget::~MainWidget() {
  delete mItemModel;
}

void MainWidget::initMainGui() {
  auto nodeWindow = new QWidget(this);
  auto fileWindow = new QWidget(this);
  auto inspectorWindow = new QWidget(this);
  auto objectPropertiesWindow = new QWidget(this);
  auto dockWindowsMenu = mWindowsMenu->addMenu(tr("Docks Windows"));
  UiWindowsCreator createLayouts;
  UiFilesWindowsCreator filesWindowCreator;

  auto nodeLayout = new QVBoxLayout();
  mNodeTreeView = new QTreeView(this);
  mNodeMouseHandler = createLayouts.installEventFilterOnTreeView(mNodeTreeView, this);
  QVBoxLayout* nodeTreeLayout;
  auto nodeTuple = createLayouts.createNodeLayout(mNodeTreeView, nodeWindow);
  nodeTreeLayout = std::get<0>(nodeTuple);
  mItemModel = std::get<1>(nodeTuple);
  nodeLayout->addLayout(nodeTreeLayout);
  nodeWindow->setLayout(nodeLayout);

  auto fileLayout = new QVBoxLayout();
  mFilesTreeView = new QTreeView(this);
  fileLayout->addLayout(filesWindowCreator.createFileSystemTree(mFilesTreeView, this));
  fileWindow->setLayout(fileLayout);

  auto inspectorLayout = new QVBoxLayout();
  mInspectorArea = new QScrollArea(this);
  inspectorLayout->addLayout(createLayouts.createInspectorViewLayout(mInspectorArea, inspectorWindow));
  inspectorWindow->setLayout(inspectorLayout);

  auto propertiesLayout = new QVBoxLayout();
  mObjectPropertiesView = new QTreeView(this);
  propertiesLayout->addLayout(createLayouts.createObjectPropertiesLayout(mObjectPropertiesView,
                                                                         objectPropertiesWindow));
  objectPropertiesWindow->setLayout(propertiesLayout);
  createDock("Node Area", nodeWindow, "Node", dockWindowsMenu, Qt::LeftDockWidgetArea);
  createDock("File Area", fileWindow, "Files", dockWindowsMenu, Qt::LeftDockWidgetArea);
  createDock("Inspector Area", inspectorWindow, "Inspector", dockWindowsMenu, Qt::RightDockWidgetArea);
  createDock("Properties Area", objectPropertiesWindow, "Properties", dockWindowsMenu, Qt::RightDockWidgetArea);
}

void MainWidget::createDock(QString dockName
                            , QWidget* widget
                            , QString actionName
                            , QMenu* subMenu
                            , Qt::DockWidgetArea dockArea) {
  widgets::DockWidget* dock = new widgets::DockWidget(dockName, this);
  dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  dock->setWidget(widget);
  auto dockWindowAction = new QAction(actionName, this);
  connect(dockWindowAction, &QAction::triggered, dock, &widgets::DockWidget::show);
  subMenu->addAction(dockWindowAction);
  addDockWidget(dockArea, dock, Qt::Horizontal);
}

void MainWidget::createBarMenu() {
  mFileMenu = menuBar()->addMenu(tr("File"));
  mEditMenu = menuBar()->addMenu(tr("Edit"));
  mToolsMenu = menuBar()->addMenu(tr("Tools"));
  mWindowsMenu = menuBar()->addMenu(tr("Windows"));
  mHelpMenu = menuBar()->addMenu(tr("Help"));
}

}
