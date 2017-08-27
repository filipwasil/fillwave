#pragma once

#include <gtest/gtest.h>
#include <memory>
#include <QVariant>
#include <QStandardItemModel>
#include "common/operations/PrepareItemUniqueId.h"

class PrepareItemUniqueIdFixture : public testing::Test {
public:
  virtual void SetUp() override {
    mModel = std::make_unique<QStandardItemModel>();
    for (int x = 0; x < 5; x++) {
      auto item = new QStandardItem();
      item->setData(QVariant(x));
      mModel->appendRow(item);
    }
  }

  virtual void TearDown() override {
  }

private:
  common::operations::PrepareItemUniqueId mSut;
  std::unique_ptr<QStandardItemModel> mModel;
};



