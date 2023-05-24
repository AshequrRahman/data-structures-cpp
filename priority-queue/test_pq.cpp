#include <iostream>

#include "gtest/gtest.h"
#include "priority_queue.h"

// Fixture class
class PQTest : public ::testing::Test {
   protected:
    PQTest() {}
    ~PQTest() override {}

    void SetUp() override {
        for (auto el : arr1) {
            pq0_.insert(el);
        }
    }

    void TearDown() override {}

    std::vector<int> arr1{13, 16, 21};
    // std::vector<int> arr1{16, 13, 21, 65, 26, 24, 32, 31, 19, 68};
    PriorityQueue<int> pq0_;
};

// Test 1: Test insert (no percolation needed)
TEST_F(PQTest, SimpleInsertWorking) {
    pq0_.print();
    ASSERT_TRUE(pq0_.isEqual(arr1));
}

// Test 2: Test insert (with percolation)
TEST_F(PQTest, PercolatedInsertWorking) {
    // 1 step percolation
    pq0_.insert(15);
    std::vector<int> res{13, 15, 21, 16};
    EXPECT_TRUE(pq0_.isEqual(res));

    // 2 step percolation
    pq0_.insert(2);
    res = {2, 13, 21, 16, 15};
    EXPECT_TRUE(pq0_.isEqual(res));
}

// Test 3: Test pop with all types of percolation
TEST_F(PQTest, PercolatedPopWorking) {
    // 1. simple pop, test left present
    pq0_.pop();
    std::vector<int> res{16, 21};
    EXPECT_TRUE(pq0_.isEqual(res));

    // 2. simple pop, test left-right present
    res = {4,5,7,31,18,10};
    PriorityQueue<int> pq1_;
    for (auto el : res) pq1_.insert(el);
    pq1_.pop();
    res = {5,10,7,31,18};
    EXPECT_TRUE(pq1_.isEqual(res));

    // 3. simple pop, from leaf
    res = {5};
    PriorityQueue<int> pq2_;
    for (auto el : res) pq2_.insert(el);
    pq2_.pop();
    EXPECT_TRUE(pq2_.isEmpty());

    EXPECT_ANY_THROW(pq2_.pop());
}

// Test 4: Test increase/decrease key
TEST_F(PQTest, IncDecWorking) {
    int deltaVal = 3;
    std::vector<int> res = {4, 5, 7, 31, 18, 10};
    PriorityQueue<int> pq1_;
    for (auto el : res) pq1_.insert(el - deltaVal);

    pq1_.increaseAllKeys(deltaVal);
    EXPECT_TRUE(pq1_.isEqual(res));

    for (auto& el : res) el -= deltaVal;
    pq1_.decreaseAllKeys(deltaVal);
    EXPECT_TRUE(pq1_.isEqual(res));
}

// Test 4: Test heapify
TEST_F(PQTest, HeapifyWorking) {
    // copy construct with already valid heap
    std::vector<int> res = {4, 5, 7, 31, 18, 10};
    PriorityQueue<int> pq1_{res};
    EXPECT_TRUE(pq1_.isEqual(res));

    // copy construct with invalid heap
    std::vector<int> initHeap = {7, 5, 4, 18, 10, 31};
    PriorityQueue<int> pq2_{initHeap};
    res = {4, 5, 7, 18, 10, 31};
    EXPECT_TRUE(pq2_.isEqual(res));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}