#include "gtest/gtest.h"
#include "stack_ll.h"

#include <iostream>

// Fixture class
class StackLLTest : public ::testing::Test {
   protected:
    StackLLTest() {}
    ~StackLLTest() override {}

    void SetUp() override {}

    void TearDown() override {}

    StackLL<int> s0_;
};

// All test are with int object

// Test 1: push is working
TEST_F(StackLLTest, PushWorking) {
    int val = 5;

    // push with l value
    s0_.push(val);
    ASSERT_EQ(s0_.size(), 1);
    EXPECT_EQ(s0_.front(), val);

    // enstack with r value
    s0_.push(33);
    ASSERT_EQ(s0_.size(), 2);
    EXPECT_EQ(s0_.front(), 33);
}

// Test 2: pop is working
TEST_F(StackLLTest, PopWorking) {
    int stackLen = 10;
    for (int i = 0; i < stackLen; ++i) s0_.push(23 + i);

    // pop non-empy stack
    for (int i = stackLen-1; i >= 0; --i) {
        EXPECT_EQ(s0_.pop(), 23 + i);
        EXPECT_EQ(s0_.size(), i);
    }

    // pop empty stack
    EXPECT_ANY_THROW(s0_.pop());
}

// Test 3: copy constructor is working
TEST_F(StackLLTest, CopyConstructorWorking) {
    // reference stack s0_
    for (int i = 0; i < 10; ++i) s0_.push(i);

    // copy construct
    StackLL<int> sCpConstruct{s0_};
    ASSERT_TRUE(s0_ == sCpConstruct);

    s0_.push(99);
    ASSERT_FALSE(s0_ == sCpConstruct);

}

// Test 4: move constructor is working
TEST_F(StackLLTest, MoveConstructorWorking) {
    // reference stack s0_
    for (int i = 0; i < 10; ++i) s0_.push(i);

    // copy for future checking
    StackLL<int> s0_copy{s0_};

    StackLL<int> sMvConstruct{std::move(s0_)};
    
    ASSERT_TRUE(s0_copy == sMvConstruct);
    ASSERT_TRUE(s0_.isEmpty());
}

// Test 5: copy assignment is working
TEST_F(StackLLTest, CopyAsnWorking) {
    // reference stack s0_
    for (int i = 0; i < 10; ++i) s0_.push(i);
    StackLL<int> sCpAsn;
    sCpAsn = s0_;

    ASSERT_TRUE(s0_ == sCpAsn);
    sCpAsn.push(-200);
    ASSERT_FALSE(s0_ == sCpAsn);
}

// Test 6: move assignment is working
TEST_F(StackLLTest, MoveAsnWorking) {
    // reference stack s0_
    for (int i = 0; i < 10; ++i) s0_.push(i);
    StackLL<int> s0_copy{s0_};

    // reference stack s1_
    StackLL<int> s1_;
    for (int i = 0; i < 10; ++i) s1_.push(i);

    StackLL<int> sMvAsn{s1_};
    sMvAsn = std::move(s0_);

    ASSERT_TRUE(sMvAsn == s0_copy);
    ASSERT_TRUE(s0_ == s1_);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}