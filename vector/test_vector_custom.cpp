#include <iostream>

#include "gtest/gtest.h"
#include "vectorCustom.h"

// fixture class
class TestVectorCustom : public ::testing::Test {
   protected:
    TestVectorCustom() {}
    ~TestVectorCustom() override {}
    void SetUp() override {
        int l_val = 5;
        vec1_.push_back(l_val);
        vec1_.push_back(-2);
        vec1_.push_back(4);
        vec1_.print_vector();
    }
    void TearDown() override {}
    VectorCustom<int> vec1_;
};

// Test 1: simple push back working
TEST_F(TestVectorCustom, SimplePushBackWorking) {
    ASSERT_EQ(vec1_[0], 5);
    ASSERT_EQ(vec1_[1], -2);
    ASSERT_EQ(vec1_[2], 4);
    EXPECT_ANY_THROW(vec1_[3]);
}

// Test 2: simple pop back working
TEST_F(TestVectorCustom, SimplePopBackWorking) {
    ASSERT_EQ(vec1_.pop_back(), 4);
    ASSERT_EQ(vec1_.pop_back(), -2);
    ASSERT_EQ(vec1_.pop_back(), 5);
    EXPECT_ANY_THROW(vec1_.pop_back());
}

// Test 3: push back with resize
TEST_F(TestVectorCustom, ResizePushBackWorking) {
    VectorCustom<int> vec2_;
    for (int idx = 0; idx < 16; ++idx) {
        vec2_.push_back(idx);
    }
    vec2_.push_back(16);

    for (int idx = 0; idx <= 16; ++idx) {
        ASSERT_EQ(vec2_[idx], idx);
    }
}

// Test 4: test iterators
TEST_F(TestVectorCustom, IteratorsWorking) {
    VectorCustom<int> vec2_;
    for (int idx = 0; idx < 16; ++idx) {
        vec2_.push_back(idx);
    }
    int idx = 0;
    for (auto it = vec2_.begin(); it != vec2_.end(); ++it, ++idx) {
        EXPECT_EQ(*it, idx);
    }
}

// Test 5: copy constructor
TEST_F(TestVectorCustom, CpConstructWorking) {
    VectorCustom<int> vec2_{vec1_};
    EXPECT_TRUE(vec2_ == vec1_);
    vec1_.push_back(99);
    EXPECT_FALSE(vec2_ == vec1_);
}

// Test 6: move constructor
TEST_F(TestVectorCustom, MvConstructWorking) {
    VectorCustom<int> vec1_cp{vec1_};
    VectorCustom<int> vec2_{std::move(vec1_)};
    EXPECT_TRUE(vec2_ == vec1_cp);
    EXPECT_TRUE(vec1_.isEmpty());
}

// Test 7: copy assignment
TEST_F(TestVectorCustom, CpAsnWorking) {
    VectorCustom<int> vec2_;
    vec2_ = vec1_;
    EXPECT_TRUE(vec2_ == vec1_);
    vec1_.push_back(99);
    EXPECT_FALSE(vec2_ == vec1_);
}

// Test 8: move assignment
TEST_F(TestVectorCustom, MvAsnWorking) {
    VectorCustom<int> vec1_cp{vec1_};
    VectorCustom<int> vec2_{vec1_};
    vec2_.push_back(99);
    VectorCustom<int> vec2_cp{vec2_};

    vec2_ = std::move(vec1_);
    EXPECT_TRUE(vec2_ == vec1_cp);
    EXPECT_TRUE(vec1_ == vec2_cp);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}