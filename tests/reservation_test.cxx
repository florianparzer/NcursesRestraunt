#include "gtest/gtest.h"

extern "C" {
    #include "../include/resFunctions.h"
}

TEST(myproject_unit_tests, Addition) {
    EXPECT_EQ(a8, 8);
}

/*
TEST(myproject_unit_tests, Multiplication) {
    EXPECT_EQ(multiply(2,4), 8);
}

TEST(myproject_unit_tests, branch) {

    EXPECT_EQ(branch(0), 8);
    EXPECT_EQ(branch(1), 8);
}
*/
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
