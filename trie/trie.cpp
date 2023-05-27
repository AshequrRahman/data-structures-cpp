#include "trie.h"

/**
 * construct with list of strings
 */
Trie::Trie(const vector<string>& srcStringList) {
    root = new TrieNode{};
    for (const string& word : srcStringList) {
        addWord(word);
    }
}

/**
 * copy constructor
 */
Trie::Trie(const Trie& srcTrie) { root = deepCopy(srcTrie.root); }

/**
 * move constructor
 */
Trie::Trie(Trie&& srcTrie) : root{srcTrie.root} { srcTrie.root = nullptr; }

/**
 * copy assignment
 */
Trie& Trie::operator=(const Trie& srcTrie) {
    if (this != &srcTrie) {
        clear();
        root = deepCopy(srcTrie.root);
    }
    return *this;
}

/**
 * move assignment
 */
Trie& Trie::operator=(Trie&& srcTrie) {
    std::swap(srcTrie.root, root);
    return *this;
}

/**
 * destructor
 */
Trie::~Trie() { clear(); }

/**
 *  add word in the trie
 */
void Trie::addWord(const string& s) {
    if (!root) root = new TrieNode{};
    TrieNode* curNode = root;
    for (char c : s) {
        if (!curNode->nextNodes[c]) {
            curNode->nextNodes[c] = new TrieNode{};
        }
        curNode = curNode->nextNodes[c];
    }
    curNode->endOfWord = true;
}

/**
 * word search
 */
bool Trie::wordSearch(const string& s) {
    if (!root) return false;
    TrieNode* curNode = root;
    for (char c : s) {
        if (!curNode->nextNodes[c]) {
            return false;
        }
        curNode = curNode->nextNodes[c];
    }
    return curNode->endOfWord;
}

/**
 * prefix search
 */
bool Trie::prefixSearch(const string& s) {
    if (!root) return false;
    TrieNode* curNode = root;
    for (char c : s) {
        if (!curNode->nextNodes[c]) {
            return false;
        }
        curNode = curNode->nextNodes[c];
    }
    return true;
}

/**
 * return all words matching prefix
 */
vector<string> Trie::allPossibleWords(const string& s) {
    vector<string> res{};
    if (!root) return res;
    TrieNode* curNode = root;
    for (char c : s) {
        if (!curNode->nextNodes[c]) {
            return res;
        }
        curNode = curNode->nextNodes[c];
    }
    // if (curNode->endOfWord) res.push_back(s);

    backtrack(curNode, res, s);
    return res;
}

/**
 * clear tree
 */
void Trie::clear() { clear(root); }

//==============================================================
// PRIVATE METHODS
//==============================================================
typename Trie::TrieNode* Trie::deepCopy(TrieNode* srcNode) {
    if (!srcNode) return nullptr;
    TrieNode* newNode = new TrieNode{};
    for (int idx = 0; idx < numElem; ++idx) {
        newNode->nextNodes[idx] = deepCopy(srcNode->nextNodes[idx]);
    }
    newNode->endOfWord = srcNode->endOfWord;
    return newNode;
}

void Trie::clear(TrieNode*& node) {
    if (!node) return;
    for (int idx = 0; idx < numElem; ++idx) {
        clear(node->nextNodes[idx]);
    }
    delete node;
    node = nullptr;
    return;
}

void Trie::backtrack(TrieNode* node, vector<string>& res, string prevWord) {
    if (!node) return;
    if (node->endOfWord) res.push_back(prevWord);
    for (int idx = 0; idx < numElem; ++idx) {
        // choose
        prevWord += idx;
        // explore
        backtrack(node->nextNodes[idx], res, prevWord);
        // unchoose
        prevWord.pop_back();
    }
}