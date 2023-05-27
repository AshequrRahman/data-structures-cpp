#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "trie.h"

using std::string;
using std::vector;

class TestTrie : public ::testing::Test {
   protected:
    TestTrie() {}
    ~TestTrie() {}
    void SetUp() override {
        wordList = {"apple", "pie",    "banana", "application",
                    "apply", "applet", "app"};
        for (const auto& word : wordList) trie1_.addWord(word);
    }
    void TearDown() override {}

    vector<string> wordList;
    Trie trie1_;
};

// Test-1: simple addword working
TEST_F(TestTrie, SimpleAddWordWorking) {
    for (const auto& word : wordList) ASSERT_TRUE(trie1_.wordSearch(word));
}

// Test-2: simple prefixsearch working
TEST_F(TestTrie, SimplePrefixSearchWorking) {
    for (const auto& word : wordList) {
        for (int idx = 0; idx < word.length(); ++idx) {
            ASSERT_TRUE(trie1_.prefixSearch(word.substr(0, idx + 1)));
        }
    }
}

// Test-3: all words with prefix working
TEST_F(TestTrie, AllPossibleWordsWorking) {
    string s = "app";
    ASSERT_TRUE(trie1_.prefixSearch(s));
    vector<string> out = trie1_.allPossibleWords(s);
    vector<string> res = {"app", "apple", "applet", "application", "apply"};
    EXPECT_EQ(res, out);
}

// Test-4: copy construct
TEST_F(TestTrie, CpCnWorking) { 
    Trie trie1_cp{trie1_}; 
    for (const auto& word : wordList) {
        ASSERT_TRUE(trie1_cp.wordSearch(word));
    }

    trie1_cp.addWord("foo");
    ASSERT_FALSE(trie1_.wordSearch("foo"));
}

// Test-5: move construct
TEST_F(TestTrie, MvCnWorking) { 
    Trie trie1_mv{std::move(trie1_)};
    std::cout << "worl" << std::endl;
    for (const auto& word : wordList) {
        ASSERT_TRUE(trie1_mv.wordSearch(word));
        ASSERT_FALSE(trie1_.wordSearch(word));
    }
}

// Test-6: copy assignment
TEST_F(TestTrie, CpAsnWorking) {
    Trie trie1_cp;
    trie1_cp = trie1_;
    for (const auto& word : wordList) {
        ASSERT_TRUE(trie1_cp.wordSearch(word));
    }

    trie1_cp.addWord("foo");
    ASSERT_FALSE(trie1_.wordSearch("foo"));
}

// Test-7: move assignment
TEST_F(TestTrie, MvAsnWorking) {
    Trie trie1_mv;
    trie1_mv = std::move(trie1_);
    for (const auto& word : wordList) {
        ASSERT_TRUE(trie1_mv.wordSearch(word));
        ASSERT_FALSE(trie1_.wordSearch(word));
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}