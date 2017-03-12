#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QApplication>

int main(int argc, char **argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  QApplication app(argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}