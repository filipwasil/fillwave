#pragma once

#include <example.h>
#include <ContextGLFW.h>

class TestModel : public flw::flf::Model {
 public:
  TestModel();

  ~TestModel() override;

  TestModel& operator=(const TestModel&);
};
