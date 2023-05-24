#include <iostream>

#include "bst_lazy.h"
#include "gtest/gtest.h"

// Fixture class
class BSTLazyTest : public ::testing::Test {
   protected:
    BSTLazyTest() {}
    ~BSTLazyTest() override {}

    void SetUp() override {
        int r_val = 6;
        b0_.insert(r_val);
        b0_.insert(2);
        b0_.insert(8);
        b0_.insert(1);
        b0_.insert(3);
    }

    void TearDown() override {}

    BST<int> b0_;
};

// All test are with int object
// Test-1: simple insert working
TEST_F(BSTLazyTest, SimpleInsertWorking) {
    vector<pair<int, int>> in_order_arr{{1, 1}, {2, 1}, {3, 1}, {6, 1}, {8, 1}};
    vector<pair<int, int>> pre_order_arr{
        {6, 1}, {2, 1}, {1, 1}, {3, 1}, {8, 1}};
    vector<pair<int, int>> post_order_arr{
        {1, 1}, {3, 1}, {2, 1}, {8, 1}, {6, 1}};

    EXPECT_EQ(b0_.inOrderTraverse(), in_order_arr);
    EXPECT_EQ(b0_.preOrderTraverse(), pre_order_arr);
    EXPECT_EQ(b0_.postOrderTraverse(), post_order_arr);
}

// Test-2: duplicate insert working
TEST_F(BSTLazyTest, DuplicateInsertWorking) {
    b0_.insert(8);
    b0_.printTree();

    vector<pair<int, int>> in_order_arr{{1, 1}, {2, 1}, {3, 1}, {6, 1}, {8, 2}};
    vector<pair<int, int>> pre_order_arr{
        {6, 1}, {2, 1}, {1, 1}, {3, 1}, {8, 2}};
    vector<pair<int, int>> post_order_arr{
        {1, 1}, {3, 1}, {2, 1}, {8, 2}, {6, 1}};

    EXPECT_EQ(b0_.inOrderTraverse(), in_order_arr);
    EXPECT_EQ(b0_.preOrderTraverse(), pre_order_arr);
    EXPECT_EQ(b0_.postOrderTraverse(), post_order_arr);
}

// Test-3: lazy erase working
TEST_F(BSTLazyTest, LazyEraseWorking) {
    b0_.insert(8);
    b0_.erase(2);
    b0_.erase(2);
    b0_.printTree();

    vector<pair<int, int>> in_order_arr{{1, 1}, {2, 0}, {3, 1}, {6, 1}, {8, 2}};
    vector<pair<int, int>> pre_order_arr{
        {6, 1}, {2, 0}, {1, 1}, {3, 1}, {8, 2}};
    vector<pair<int, int>> post_order_arr{
        {1, 1}, {3, 1}, {2, 0}, {8, 2}, {6, 1}};

    EXPECT_EQ(b0_.inOrderTraverse(), in_order_arr);
    EXPECT_EQ(b0_.preOrderTraverse(), pre_order_arr);
    EXPECT_EQ(b0_.postOrderTraverse(), post_order_arr);
}

// Test-4: simple min-max working
TEST_F(BSTLazyTest, SimpleMinMaxWorking) {
    EXPECT_EQ(b0_.findMax(), 8);
    EXPECT_EQ(b0_.findMin(), 1);
}

// Test-5: lazy min working
TEST_F(BSTLazyTest, LazyMinWorking) {
    b0_.erase(1);
    EXPECT_EQ(b0_.findMin(), 2);
    b0_.erase(2);
    EXPECT_EQ(b0_.findMin(), 3);
    b0_.erase(3);
    EXPECT_EQ(b0_.findMin(), 6);
    b0_.erase(6);
    EXPECT_EQ(b0_.findMin(), 8);
    b0_.erase(8);
    EXPECT_ANY_THROW(b0_.findMin());
}

// Test-6: lazy max working
TEST_F(BSTLazyTest, LazyMaxWorking) {
    b0_.erase(8);
    EXPECT_EQ(b0_.findMax(), 6);
    b0_.erase(6);
    EXPECT_EQ(b0_.findMax(), 3);
    b0_.erase(3);
    EXPECT_EQ(b0_.findMax(), 2);
    b0_.erase(2);
    EXPECT_EQ(b0_.findMax(), 1);
    b0_.erase(1);
    EXPECT_ANY_THROW(b0_.findMax());
}

// Test-7: copy constructor working
TEST_F(BSTLazyTest, CopyConstructWorking) {
    BST<int> bCopyConst{b0_};
    EXPECT_TRUE(b0_ == bCopyConst);
    b0_.insert(9);
    EXPECT_FALSE(b0_ == bCopyConst);
}

// Test-8: move constructor working
TEST_F(BSTLazyTest, MoveConstructWorking) {
    BST<int> b0_copy{b0_};
    BST<int> bMvConstruct{std::move(b0_)};

    EXPECT_TRUE(b0_copy == bMvConstruct);
    EXPECT_TRUE(b0_.empty());
}

// Test-9: copy assignment working
TEST_F(BSTLazyTest, CopyAsnWorking) {
    BST<int> bCopyAsn;
    bCopyAsn = b0_;
    EXPECT_TRUE(b0_ == bCopyAsn);
    b0_.insert(9);
    EXPECT_FALSE(b0_ == bCopyAsn);
}

// Test-8: move constructor working
TEST_F(BSTLazyTest, MoveAsnWorking) {
    BST<int> b0_copy{b0_};
    BST<int> bMvAsn{b0_};
    bMvAsn.insert(10);

    bMvAsn = std::move(b0_);
    EXPECT_TRUE(b0_copy == bMvAsn);
    EXPECT_FALSE(b0_ == bMvAsn);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}