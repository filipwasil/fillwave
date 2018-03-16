#include "../common.h"

#include <fillwave/Fillwave.h>
#include <fillwave/common/pointers/PointerCache.h>

#include <iostream>

using namespace flw;
using namespace flw::flf;

struct DualInt {
  DualInt()
    : a(99)
    , b(88) {
    // nothing
  }

  DualInt(int aa, int bb)
    : a(aa)
    , b(bb) {
    // nothing
  }

  ~DualInt() {
    // nothing
  }

  int a;
  int b;
};

bool operator == (DualInt const& lhs, DualInt const& rhs) {
  return lhs.a == rhs.a && lhs.b == rhs.b;
}

bool operator != (DualInt const& lhs, DualInt const& rhs) {
  return lhs.a != rhs.a || lhs.b != rhs.b;
}

TEST (PointerCache, definingIntPointer) {
  PointerCache<int> sut;
  EXPECT_EQ (1, 1);
}

TEST (PointerCache, definingIntPointerConstructionWithArguments) {
  PointerCache<int> sut(1);
  EXPECT_EQ (1, 1);
}

TEST (PointerCache, definingStructPointer) {
  PointerCache<DualInt> sut;
  EXPECT_EQ (1,1);
}

TEST (PointerCache, definingStructPointerConstructionWithArguments) {
  PointerCache<DualInt> sut(1, 2);
  sut = PointerCache<DualInt>(3, 7);
  EXPECT_NE (sut->a,1);
  EXPECT_EQ (sut->a,3);
  PointerCache<DualInt> sut2 = std::move(sut);
  EXPECT_EQ (sut2->b,7);
}

