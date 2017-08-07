#include <memory>
#include <QtWidgets/QLabel>
#include <QToolButton>
#include "MainWidget.h"
#include "scene/Renderer.h"

namespace common {
MainWidget::MainWidget(int argc, char *argv[], QWidget *parent)
    : QMainWindow(parent), mWidgetSplitter(new QSplitter()), mCentralWidget(new QWidget(this))
    , mScensTab(new QTabWidget()), mRenderer(new Renderer(argc, argv)), mArgc(argc), mArgv(argv) {
  createBarMenu();
  createFileSystemTree();
  createInspectorView();
  create();

  QHBoxLayout *vertical = new QHBoxLayout();
  vertical->setDirection(QBoxLayout::LeftToRight);
  QVBoxLayout *layoutEngineWindow = new QVBoxLayout();
  mRenderer->setLayout(layoutEngineWindow);

  QVBoxLayout *verticalLeft = new QVBoxLayout();
  verticalLeft->addLayout(createNodeWidget());
  verticalLeft->addLayout(createFileSystemTree());
  QWidget *leftWidget = new QWidget();
  leftWidget->setMinimumWidth(100);
  leftWidget->setLayout(verticalLeft);

  mScensTab->addTab(mRenderer, "empty");

  QVBoxLayout *verticalRight = new QVBoxLayout();
  verticalRight->addLayout(createInspectorView());
  verticalRight->addLayout(createOther());
  QWidget *rightWidget = new QWidget();
  rightWidget->setMinimumWidth(100);
  rightWidget->setLayout(verticalRight);

  mWidgetSplitter->addWidget(leftWidget);
  mWidgetSplitter->addWidget(mScensTab);
  mWidgetSplitter->addWidget(rightWidget);
  QList<int> sizeList = {100,mWindowHeight - 200,100};

  mWidgetSplitter->setSizes(sizeList);
  this->setCentralWidget(mWidgetSplitter);
  resize(mWindowWidth, mWindowHeight);
}

MainWidget::~MainWidget() {

}

void MainWidget::createBarMenu() {
  mFileMenu = menuBar()->addMenu(tr("&File"));
  mEditMenu = menuBar()->addMenu(tr("&Edit"));
  mToolsMenu = menuBar()->addMenu(tr("&Tools"));
  mHelpMenu = menuBar()->addMenu(tr("&Help"));
}

QVBoxLayout *MainWidget::createNodeWidget() {
  QLabel *label = new QLabel("Node");
  label->setAlignment(Qt::AlignHCenter);
  QToolButton *addNode = new QToolButton();
  addNode->setIcon(QIcon("icons/add.png"));
  QToolButton *deleteNode = new QToolButton();
  deleteNode->setIcon(QIcon("icons/delete.png"));
  QHBoxLayout *hBox = new QHBoxLayout();
  hBox->addWidget(addNode);
  hBox->addWidget(deleteNode);
  mScenTree = new QTreeWidget();
  mScenTree->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  QVBoxLayout *vBox = new QVBoxLayout();
  vBox->addWidget(label);
  vBox->addLayout(hBox);
  vBox->addWidget(mScenTree);
  return vBox;
}

QVBoxLayout *MainWidget::createFileSystemTree() {
  QLabel *label = new QLabel("File System");
  label->setAlignment(Qt::AlignHCenter);
  QToolButton *addFolder = new QToolButton();
  addFolder->setIcon(QIcon("icons/newFolder.jpg"));
  QToolButton *deleteFolder = new QToolButton();
  deleteFolder->setIcon(QIcon("icons/delete.png"));
  QHBoxLayout *hBox = new QHBoxLayout();
  hBox->addWidget(addFolder);
  hBox->addWidget(deleteFolder);
  mFileSystemTree = new QTreeWidget();
  mFileSystemTree->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  QVBoxLayout *vBox = new QVBoxLayout();
  vBox->addWidget(label);
  vBox->addLayout(hBox);
  vBox->addWidget(mFileSystemTree);
  return vBox;
}

QVBoxLayout *MainWidget::createInspectorView() {
  QLabel *label = new QLabel("Inspector");
  label->setAlignment(Qt::AlignHCenter);

  mInspectorTree = new QTreeWidget();
  mInspectorTree->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  QVBoxLayout *vBox = new QVBoxLayout();
  vBox->addWidget(label);
  vBox->addWidget(mInspectorTree);
  return vBox;
}

QVBoxLayout *MainWidget::createOther() {
  QLabel *label = new QLabel("Other");
  label->setAlignment(Qt::AlignHCenter);

  mOther = new QTreeWidget();
  mOther->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  QVBoxLayout *vBox = new QVBoxLayout();
  vBox->addWidget(label);
  vBox->addWidget(mOther);
  return vBox;
}

}
