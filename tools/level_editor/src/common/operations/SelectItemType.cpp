#include <memory>
#include <QDialog>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "SelectItemType.h"

namespace common {

SelectItemType::SelectItemType()
  : mItemListModel(new QStandardItemModel(this))
  , mMainWidget(new QDialog(Q_NULLPTR)) {
  mItemListTreeView = new QTreeView(mMainWidget);
  QStandardItem* item = new QStandardItem(common::ItemTypeString[EItemType::threeDObject]);
  mItemListModel->setItem(0, 0, item);

  mItemListTreeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  mItemListTreeView->setMinimumSize(400, 500);
  mItemListTreeView->setHeaderHidden(true);
  mItemListTreeView->setModel(mItemListModel);
}

SelectItemType::~SelectItemType() {
  delete mMainWidget;
}

bool SelectItemType::show() {
  mMainWidget->setObjectName("Item chooser");
  auto* layout = new QVBoxLayout();
  layout->addWidget(mItemListTreeView);
  auto* buttonLayout = new QHBoxLayout();
  QPushButton* ok = new QPushButton("Ok", mMainWidget);
  QPushButton* cancel = new QPushButton("Cancel", mMainWidget);
  bool operationStatus = false;
  connect(ok, &QPushButton::clicked, [this, &operationStatus]() {
    selectedType(operationStatus);
  });
  connect(cancel, &QPushButton::clicked, [this, &operationStatus]() {
    operationStatus = false;
    mMainWidget->close();
  });

  buttonLayout->addStretch(1);
  buttonLayout->addWidget(ok);
  buttonLayout->addWidget(cancel);

  layout->addLayout(buttonLayout);
  mMainWidget->setLayout(layout);
  mMainWidget->setMinimumSize(400, 800);
  mMainWidget->exec();
  return operationStatus;
}

void SelectItemType::selectedType(bool& operationStatus) {
  auto selectedIndexModel = mItemListTreeView->selectionModel()->selectedIndexes();
  if (selectedIndexModel.empty()) {
    operationStatus = false;
    return;
  }
  QString type = mItemListModel->itemFromIndex(selectedIndexModel.first())->text();

  mItemType = common::ItemTypeString.key(type);
  bool ok = false;
  QString text =
    QInputDialog::getText(
      mMainWidget,
      "QInputDialog::getText()",
      "User name:",
      QLineEdit::Normal,
      "",
      &ok);
  if (ok && !text.isEmpty()) {
    mItemName = text;
    operationStatus = true;
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