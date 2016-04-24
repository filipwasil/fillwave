/*
 * Button.cpp
 *
 *  Created on: Jan 17, 2016
 *      Author: filip
 */

#include <fillwave/Log.h>
#include <fillwave/Fillwave.h>
#include "../mocks/Button.h"

FLOGINIT_DEFAULT()

using namespace fillwave;
using namespace fillwave::framework;

using ::testing::AtLeast;
using ::testing::Return;

TEST(ButtonTest, CanBePicked) {

}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
