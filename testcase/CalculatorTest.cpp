#include "TestHelper.h"

class CalculatorTest: public TestHelper {
public:
    static void SetUpTestSuite() {
        printf("set up CalculatorTest\n");
    };
    static void TearDownTestSuite() {
        printf("tear down CalculatorTest\n");
    };
};

TEST_F(CalculatorTest, simple_add_function_ok) {
    EXPECT_EQ(2 + 2, 4);
    EXPECT_NE(1, 0);
    EXPECT_TRUE(true);
    EXPECT_FALSE(false);
}

TEST_F(CalculatorTest, simple_sub_function_ok) {
    ASSERT_EQ(5 - 3, 2);
    ASSERT_NE(10, 5);
    ASSERT_TRUE(1);
    ASSERT_FALSE(0);
    ASSERT_FALSE(false);
}
