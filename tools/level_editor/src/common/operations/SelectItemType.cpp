#include <memory>
#include <QDialog>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "SelectItemType.h"

namespace common {

SelectItemType::SelectItemType() {
  mItemListModel = new QStandardItemModel();
  mItemTypes["QBasicItem"] = EItemType::Object;
  QStandardItem* item = new QStandardItem("QBasicItem");
  mItemListModel->setItem(0, 0, item);

  mItemListTreeView = new QTreeView();
  mItemListTreeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  mItemListTreeView->setMinimumSize(400, 500);
  mItemListTreeView->setHeaderHidden(true);
  mItemListTreeView->setModel(mItemListModel);
  mMainWidget = nullptr;
  mOperationStatus = false;
}

SelectItemType::~SelectItemType() {
  delete mItemListTreeView;
  delete mItemListModel;
  delete mMainWidget;
}

bool SelectItemType::show() {
  mMainWidget = new QDialog();
  mMainWidget->setObjectName("Item chooser");
  auto* layout = new QVBoxLayout();
  layout->addWidget(mItemListTreeView);
  auto* buttonLayout = new QHBoxLayout();
  QPushButton* ok = new QPushButton("Ok", mMainWidget);
  QPushButton* cancel = new QPushButton("Cancel", mMainWidget);
  connect(ok, &QPushButton::clicked, this, &SelectItemType::selectedType);
  connect(cancel, &QPushButton::clicked, [this]() {
    mOperationStatus = false;
    mMainWidget->close();
  });

  buttonLayout->addStretch(1);
  buttonLayout->addWidget(ok);
  buttonLayout->addWidget(cancel);

  layout->addLayout(buttonLayout);
  mMainWidget->setLayout(layout);
  mMainWidget->setMinimumSize(400, 800);
  mMainWidget->exec();
  return mOperationStatus;
}

void SelectItemType::selectedType() {
  auto selectedIndexModel = mItemListTreeView->selectionModel()->selectedIndexes();
  if (selectedIndexModel.empty()) {
    mOperationStatus = false;
    return;
  }
  QString type = mItemListModel->itemFromIndex(selectedIndexModel.first())->text();
  mItemType = mItemTypes[type];
  bool ok;
  QString text = QInputDialog::getText(mMainWidget,
                                       "QInputDialog::getText()",
                                       "User name:",
                                       QLineEdit::Normal,
                                       "",
                                       &ok);
  if (ok && !text.isEmpty()) {
    mItemName = text;
    mOperationStatus = true;
  }
  mMainWidget->close();
}

EItemType SelectItemType::getItemType() const {
  return mItemType;
}

const QString& SelectItemType::getItemName() const {
  return mItemName;
}

}