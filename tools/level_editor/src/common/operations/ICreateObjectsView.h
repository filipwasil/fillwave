#pragma once

#include <QString>
#include "common/InternalTypes.h"
namespace common
{
class ICreateObjectsView
{
 public:
  virtual ~ICreateObjectsView() = default;
  virtual void execute() = 0;
  virtual QString getName() = 0;
  virtual EItemType getType() = 0;
};
}