#include "UUID.h"

namespace common {
QByteArray UUID::getId() {
  return QUuid::createUuid().toByteArray();
}

bool UUID::comapreArrays(QByteArray* array1, QByteArray* array2) {
  for (int i = 0; i < array1->size(); i++) {
    if (array1[i] != array2[i]) {
      return false;
    }
  }
  return true;
}
}