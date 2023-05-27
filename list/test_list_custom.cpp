#include <iostream>
#include <vector>

#include "gtest/gtest.h"
#include "listCustom.h"

class TestListCustom : public ::testing::Test {
   protected:
    TestListCustom() {}
    ~TestListCustom() {}
    void SetUp() override {
        items = {11, 20, 12, 76, 81, 91};
        for (auto& item : items) list1_.insert_front(item);
    }
    void TearDown() override {}

    ListCustom<int> list1_;
    std::vector<int> items;
};

// Test-1: simple insert working
TEST_F(TestListCustom, SimpleInsertWorking) {
    // test insert front
    int idxRes = items.size() - 1;
    auto it = list1_.begin();
    for (it = list1_.begin(); it != list1_.end(); ++it, --idxRes) {
        ASSERT_EQ(*it, items[idxRes]);
    }

    // test insert front
    int backVal = 99;
    list1_.insert_back(backVal);
    ASSERT_EQ(*--list1_.end(), backVal);
    list1_.insert_back(std::move(backVal));
    ASSERT_EQ(*--list1_.end(), backVal);

    // test insert with indexing
    int insertedVal = 23;
    int insertIdx = 1;
    list1_.insert(insertedVal, insertIdx);
    ASSERT_EQ(*++list1_.begin(), insertedVal);

    insertIdx = 4;
    list1_.insert(std::move(insertedVal), 4);
    it = list1_.begin();
    for (int i = 0; i < insertIdx; ++i, ++it) {
    }
    ASSERT_EQ(*it, insertedVal);
}

// Test-2: erase
TEST_F(TestListCustom, EraseWorking) {
    list1_.erase_front();
    ASSERT_EQ(*list1_.begin(), items[items.size() - 2]);
    list1_.erase_back();
    ASSERT_EQ(*--list1_.end(), items[1]);
    list1_.erase(0);
    ASSERT_EQ(*list1_.begin(), items[items.size() - 3]);
    list1_.erase(1);
    ASSERT_EQ(*list1_.begin(), items[items.size() - 3]);
    ASSERT_EQ(*++list1_.begin(), items[items.size() - 5]);
}

// Test-3: indexing working
TEST_F(TestListCustom, IndexingWorking) {
    // test insert front
    int idxRes = items.size() - 1;
    auto it = list1_.begin();
    for (int idx = 0; idx != items.size(); ++idx, --idxRes) {
        ASSERT_EQ(list1_[idx], items[idxRes]);
    }
}

// Test-4: copy constructor
TEST_F(TestListCustom, CpCnWorking) {
    ListCustom<int> list1_cp{list1_};
    int idxRes = items.size() - 1;
    auto it = list1_cp.begin();
    for (it = list1_cp.begin(); it != list1_cp.end(); ++it, --idxRes) {
        ASSERT_EQ(*it, items[idxRes]);
    }
}

// Test-4: move constructor
TEST_F(TestListCustom, MvCnWorking) {
    ListCustom<int> list1_mv{std::move(list1_)};
    int idxRes = items.size() - 1;
    auto it = list1_mv.begin();
    for (it = list1_mv.begin(); it != list1_mv.end(); ++it, --idxRes) {
        ASSERT_EQ(*it, items[idxRes]);
    }
}

// Test-6: copy assignment
TEST_F(TestListCustom, CpAsnWorking) {
    ListCustom<int> list1_cp;
    list1_cp = list1_;
    int idxRes = items.size() - 1;
    auto it = list1_cp.begin();
    for (it = list1_cp.begin(); it != list1_cp.end(); ++it, --idxRes) {
        ASSERT_EQ(*it, items[idxRes]);
    }
}

// Test-7: move assignment
TEST_F(TestListCustom, MvAsnWorking) {
    ListCustom<int> list1_mv;
    list1_mv = std::move(list1_);
    int idxRes = items.size() - 1;
    auto it = list1_mv.begin();
    for (it = list1_mv.begin(); it != list1_mv.end(); ++it, --idxRes) {
        ASSERT_EQ(*it, items[idxRes]);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}