#include "../common.h"

#include <fillwave/Fillwave.h>
#include <fillwave/allocators/AllocatorHeap.h>

using namespace flw;
using namespace flw::flf;

TEST (HeapAllocator, definingIntVector) {
  std::vector<int, AllocatorHeap<int>>;
  EXPECT_EQ (1, 1);
}
