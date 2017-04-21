#include <fillwave/Log.h>
#include <fillwave/Fillwave.h>
#include "../mocks/Button.h"

using namespace flw;
using namespace flw::flf;

using ::testing::AtLeast;
using ::testing::Return;

TEST(ButtonTest, CanBePicked
) {

}

int main(int argc, char **argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
