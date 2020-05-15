#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gos/pid/ui/pathvalidator.h>

namespace gptuv = ::gos::pid::toolkit::ui::validator;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace plugin {
namespace validator {

TEST(Path, FileAbsolute) {
  gptuv::Path validator;

  QValidator::State result;
  int pos = 0;
  QString input;

  validator.setType(gptuv::Path::PATH_VALIDATOR_TYPE_FILE);
  validator.setRestriction(gptuv::Path::PATH_VALIDATOR_RESTRICTION_ABSOLUTE);

  input = "cccc.log";
  result = validator.validate(input, pos);
  EXPECT_EQ(QValidator::State::Invalid, result);

#ifdef _WIN32
  input = "C:\\file.log";
#else
#endif
  result = validator.validate(input, pos);
  EXPECT_EQ(QValidator::State::Acceptable, result);

#ifdef _WIN32
  input = "C:\\non-existing-path\\file.log";
#else
#endif
  result = validator.validate(input, pos);
  EXPECT_EQ(QValidator::State::Invalid, result);

#ifdef _WIN32
  input = "C:file.log";
#else
#endif
  result = validator.validate(input, pos);
  EXPECT_EQ(QValidator::State::Invalid, result);

#ifdef _WIN32
  input = "C:tmp\file.log";
#else
#endif
  result = validator.validate(input, pos);
  EXPECT_EQ(QValidator::State::Invalid, result);

}


} // namespace validator
} // namespace plugin
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos