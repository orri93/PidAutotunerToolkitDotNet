#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gos/pid/toolkit/stability.h>

namespace gpt = ::gos::pid::toolkit;

TEST(PidToolkitStabilityTest, Evaluate) {
  gpt::stability::Parameters<double> parameters;
  parameters.Range.lowest = 0.0;
  parameters.Range.highest = 255.0;
  parameters.Size = 30;

  gpt::stability::Variables<double> variables;
  
  gpt::stability::Results<double> results;

  gpt::stability::initialize(parameters, variables);

  gpt::stability::evaluate(parameters, variables, results, 1.0);
  EXPECT_DOUBLE_EQ(1.0, results.Mean);

  gpt::stability::evaluate(parameters, variables, results, 2.0);
  EXPECT_DOUBLE_EQ(1.5, results.Mean);

  gpt::stability::evaluate(parameters, variables, results, 3.0);
  EXPECT_DOUBLE_EQ(2.0, results.Mean);
}
