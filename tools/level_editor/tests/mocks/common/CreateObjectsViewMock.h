#pragma once

#include "gmock/gmock.h"
#include "common/operations/ICreateObjectsView.h"

namespace common {
class ICreateObjectsViewMock : public common::ICreateObjectsView {
  MOCK_METHOD0(execute, void());

  MOCK_METHOD0(getName, QString());

  MOCK_METHOD0(getType, common::EItemType());
};
}