#include <gtest/gtest.h>


namespace {
  int GetTheMeaningOfLife() { return 42; }
}

TEST(TestTopic, TrivialEquality) {
  EXPECT_EQ(GetTheMeaningOfLife(), 42);
}

TEST(TestTopic, MoreEqualityTests) {
  ASSERT_EQ(GetTheMeaningOfLife(), 0) << "failed!!";
  EXPECT_FLOAT_EQ(2.2F, 2.2F);
}
