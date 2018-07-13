#pragma once

#include <QUuid>

namespace common {
class UUID {
 public:
  QByteArray getId();
  bool comapreArrays(QByteArray* array1, QByteArray* array2);
};

}

