#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <vector>
#include <string>
using std::string;
using std::vector;

class Trie {
   public:
    // big five
    explicit Trie(const vector<string>& srcStringList = {});
    Trie(const Trie& srcTrie);
    Trie(Trie&& srcTrie);
    Trie& operator=(const Trie& srcTrie);
    Trie& operator=(Trie&& srcTrie);
    ~Trie();

    // add individual word
    void addWord(const string& s);

    // substring search
    bool prefixSearch(const string& prefix);

    // word search
    bool wordSearch(const string& s);

    // Todo: return all possible prefix-matched word
    vector<string> allPossibleWords(const string& s);

    void clear();
   private:
    static const int numElem = 128;
    struct TrieNode {
        vector<TrieNode*> nextNodes{numElem, nullptr};
        bool endOfWord = false;
    };
    TrieNode* root;
    TrieNode* deepCopy(TrieNode* node);
    void clear(TrieNode*& node);
    void backtrack(TrieNode* node, vector<string>& res, string prevWord);
};

#endif