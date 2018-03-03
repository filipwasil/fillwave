#include "../common.h"

#include <fillwave/Fillwave.h>
#include <fillwave/allocators/AllocatorStack.h>

using namespace flw;
using namespace flw::flf;

TEST (StackAllocator, definingIntVector) {
  std::vector<int, AllocatorStack<int>>;
  EXPECT_EQ (1, 1);
}
