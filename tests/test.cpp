// Copyright 2019 Gabriele Bozzola <gabrielebozzola@email.arizona.edu>

#include <gtest/gtest.h>
#include "celestiale.h"

TEST(HelloWorld, test1) {
  ASSERT_EQ(hello_world(), 1);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
