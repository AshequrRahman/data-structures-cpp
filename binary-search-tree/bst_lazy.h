#ifndef BST_H
#define BST_H

#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
template <typename TComp>
class BST {
   public:
    // Big five
    BST();
    BST(const BST& srcTree);
    BST(BST&& srcTree);
    BST& operator=(const BST& srcTree);
    BST& operator=(BST&& srcTree);
    ~BST();

    // public methods

    // find minimum and maximum values
    const TComp& findMin() const;
    const TComp& findMax() const;

    // find if element exist
    bool contains(const TComp& element) const;

    // insert element
    void insert(const TComp& element);
    void insert(TComp&& element);

    // erase/remove element
    void erase(const TComp& element);
    void erase(TComp&& element);

    // check empty / make empty
    bool empty() const;
    void clear();

    // print tree in output stream
    void printTree(ostream& out = cout) const;


    // traversals
    vector<pair<TComp,int>> inOrderTraverse() const;
    vector<pair<TComp,int>> preOrderTraverse() const;
    vector<pair<TComp,int>> postOrderTraverse() const;

    // equality
    bool operator==(BST<TComp> srcBST) const;

   private:
    struct BinaryNode {
        TComp nodeElement;
        BinaryNode* leftNode;
        BinaryNode* rightNode;
        int elementCount;

        BinaryNode(const TComp& nodeElement, BinaryNode* leftNode,
                   BinaryNode* rightNode, int elementCount)
            : nodeElement{nodeElement},
              leftNode{leftNode},
              rightNode{rightNode},
              elementCount{elementCount} {};

        BinaryNode(TComp&& nodeElement, BinaryNode* leftNode,
                   BinaryNode* rightNode, int elementCount)
            : nodeElement{std::move(nodeElement)},
              leftNode{leftNode},
              rightNode{rightNode},
              elementCount{elementCount} {};
    };

    BinaryNode* root;

    // recursive definitions of public method

    // find minimum and maximum values
    BinaryNode* findMin(BinaryNode* node) const;
    BinaryNode* findMax(BinaryNode* node) const;

    // find if element exist
    bool contains(const TComp& element, BinaryNode* node) const;

    // insert element
    void insert(const TComp& element, BinaryNode*& node);
    void insert(TComp&& element, BinaryNode*& node);

    // erase/remove element
    void erase(const TComp& element, BinaryNode*& node);
    void erase(TComp&& element, BinaryNode*& node);

    // make empty
    void clear(BinaryNode*& node);

    // print tree in output stream
    void printTree(ostream& out, BinaryNode* node) const;

    // deep copy
    BinaryNode* deepCopy(BinaryNode* node) const;

    // traversals
    void inOrderTraverse(BinaryNode* node, vector<pair<TComp,int>>& res) const;
    void preOrderTraverse(BinaryNode* node, vector<pair<TComp,int>>& res) const;
    void postOrderTraverse(BinaryNode* node, vector<pair<TComp,int>>& res) const;

    // recursive equality check
    bool isEqual(BinaryNode* node, BinaryNode* srcNode) const;
};

#endif