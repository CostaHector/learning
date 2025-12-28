#ifndef TEST_HELPER_H
#define TEST_HELPER_H
#include <gtest/gtest.h>
#include <mockcpp/mokc.h>
#include <mockcpp/GlobalMockObject.h>
#include <mockcpp/MockObject.h>
#include <mockcpp/MockObjectHelper.h>
#include <cstdio>

USING_MOCKCPP_NS;
class TestHelper: public ::testing::Test {
public:
    static void SetUpTestSuite() {
        printf("set up test suite\n");
    };
    static void TearDownTestSuite() {
        printf("tear down test suite\n");
    };

protected:
    void SetUp() override final{
        GlobalMockObject::reset();
        LLTUp();
    }
    void TearDown() override final {
        LLTDown();
        GlobalMockObject::verify();
    }
    virtual void LLTUp() {};
    virtual void LLTDown() {};
};
#endif