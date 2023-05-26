#include <iostream>
#include "gtest/gtest.h"
#include "union_find.h"

// Fixture class
class TestUnionFind : public ::testing::Test {
   protected:
    TestUnionFind() {}
    ~TestUnionFind() override {}
    void SetUp() override { initElements = {0, 1, 2, 3}; }
    void TearDown() override {}
    vector<int> initElements;
};

// Test-1: Simple vector copy constructor working
TEST_F(TestUnionFind, SimpleVectorCpConstructWorking) {
    // lvalue
    UnionFind<int> uf0_{initElements};
    unordered_map<int, int> m_res{{0, 0}, {1, 1}, {2, 2}, {3,3}};
    vector<int> vec_res{-1, -1, -1, -1};
    uf0_.printParentsAndRootSize();
    ASSERT_TRUE(uf0_.getParentVector() == vec_res);
    ASSERT_TRUE(uf0_.getMap() == m_res);

    // rvalue
    UnionFind<int> uf1_{std::move(initElements)};
    ASSERT_TRUE(uf1_.getParentVector() == vec_res);
    ASSERT_TRUE(uf1_.getMap() == m_res);
}

// Test-2: Simple Union
TEST_F(TestUnionFind, SimpleUnionWorking) {
    UnionFind<int> uf0_{initElements};
    uf0_.connect(0, 1);
    //uf0_.printParentsAndRootSize();
    EXPECT_TRUE(uf0_.isConnected(0, 1));
    uf0_.connect(2, 3);
    //uf0_.printParentsAndRootSize();
    EXPECT_TRUE(uf0_.isConnected(2, 3));

    EXPECT_FALSE(uf0_.isConnected(1, 3));
    EXPECT_FALSE(uf0_.isConnected(1, 2));
    EXPECT_FALSE(uf0_.isConnected(0, 3));
    EXPECT_FALSE(uf0_.isConnected(0, 2));
    uf0_.printParentsAndRootSize();
}

// test-3: path compression
TEST_F(TestUnionFind, PathCompWorking) {
    UnionFind<int> uf0_{initElements};
    uf0_.connect(0, 1);
    uf0_.connect(2, 3);
    uf0_.connect(1, 3);
    
    vector<int> vec_res{-4, 0, 0, 2};
    ASSERT_TRUE(uf0_.getParentVector() == vec_res);

    ASSERT_TRUE(uf0_.findRootIdxOfElement(3) == 0);
    vec_res = {-4, 0, 0, 0};
    ASSERT_TRUE(uf0_.getParentVector() == vec_res);
}

// test-4: add new element
TEST_F(TestUnionFind, AddElemWorking) {
    UnionFind<int> uf0_{initElements};
    uf0_.addElement(9);
    unordered_map<int, int> m_res{{0, 0}, {1, 1}, {2, 2}, {3, 3}, {9,4}};
    vector<int> vec_res{-1, -1, -1, -1, -1};
    uf0_.printParentsAndRootSize();
    EXPECT_EQ(uf0_.getParentVector(), vec_res);
    EXPECT_EQ(uf0_.getMap(), m_res);
}

// Test-5: copy constructor working
TEST_F(TestUnionFind, CpConstructWorking) {
    UnionFind<int> uf0_{initElements};
    UnionFind<int> uf1_{uf0_};
    EXPECT_TRUE(uf1_ == uf0_);
    uf0_.addElement(9);
    EXPECT_FALSE(uf1_ == uf0_);
}

// Test-6: move constructor working
TEST_F(TestUnionFind, MvConstructWorking) {
    UnionFind<int> uf0_{initElements};
    UnionFind<int> uf0_cp{uf0_};
    UnionFind<int> uf1_{std::move(uf0_)};
    EXPECT_TRUE(uf1_ == uf0_cp);
    EXPECT_FALSE(uf1_ == uf0_);
}

// Test-7: copy assignment working
TEST_F(TestUnionFind, CpAsnWorking) {
    UnionFind<int> uf0_{initElements};
    UnionFind<int> uf1_{{0,0}};
    uf1_ = uf0_;
    EXPECT_TRUE(uf1_ == uf0_);
    uf0_.addElement(9);
    EXPECT_FALSE(uf1_ == uf0_);
}

// Test-8: move assignment working
TEST_F(TestUnionFind, MvAsnWorking) {
    UnionFind<int> uf0_{initElements};
    UnionFind<int> uf1_{{0,0}};
    UnionFind<int> uf0_cp{uf0_};
    UnionFind<int> uf1_cp{uf1_};
    uf1_ = std::move(uf0_);
    EXPECT_TRUE(uf1_ == uf0_cp);
    EXPECT_TRUE(uf0_ == uf1_cp);
}

int main(int argc, char** argv) { 
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}