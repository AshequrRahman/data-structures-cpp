#include "bst_lazy.h"

/**
 * zero-param constructor
 */
template <typename TComp>
BST<TComp>::BST() : root{nullptr} {}

/**
 * Copy constructor
 */
template <typename TComp>
BST<TComp>::BST(const BST<TComp>& srcTree) : root{nullptr} {
    root = deepCopy(srcTree.root);
};

/**
 * Move constructor
 */
template <typename TComp>
BST<TComp>::BST(BST<TComp>&& srcTree) : root{srcTree.root} {
    srcTree.root = nullptr;
}

/**
 * Destructor
 */
template <typename TComp>
BST<TComp>::~BST() {
    clear();
}

/**
 * copy assignment
 */
template <typename TComp>
BST<TComp>& BST<TComp>::operator=(const BST<TComp>& srcBST) {
    if (this != &srcBST) {
        clear();
        root = deepCopy(srcBST.root);
    }
    return *this;
}

/**
 *  move assignment
 */
template <typename TComp>
BST<TComp>& BST<TComp>::operator=(BST<TComp>&& srcBST) {
    /*
    clear();
    root = srcBST.root;
    srcBST.root = nullptr;
    */
    // or, in one line: std::swap(root, srcBST.root)
    std::swap(root, srcBST.root);
    return *this;
}

/**
 * clear the BST
 */
template <typename TComp>
void BST<TComp>::clear() {
    clear(root);
}

/**
 * find the minimum element
 */
template <typename TComp>
const TComp& BST<TComp>::findMin() const {
    BinaryNode* minNode = findMin(root);
    if (!minNode) {
        throw std::invalid_argument("empty bst");
    }
    return minNode->nodeElement;
}

/**
 * find the maximum element
 */
template <typename TComp>
const TComp& BST<TComp>::findMax() const {
    BinaryNode* maxNode = findMax(root);
    if (!maxNode) {
        throw std::invalid_argument("empty bst");
    }
    return maxNode->nodeElement;
}

/**
 * check is BST contains an element
 */
template <typename TComp>
bool BST<TComp>::contains(const TComp& element) const {
    return contains(element, root);
}

/**
 * insert an element
 */
template <typename TComp>
void BST<TComp>::insert(const TComp& element) {
    insert(element, root);
}

template <typename TComp>
void BST<TComp>::insert(TComp&& element) {
    insert(std::move(element), root);
}

/**
 * Remove an element
 */
template <typename TComp>
void BST<TComp>::erase(const TComp& element) {
    erase(element, root);
}
template <typename TComp>
void BST<TComp>::erase(TComp&& element) {
    erase(std::move(element), root);
}

// print tree in output stream
template <typename TComp>
void BST<TComp>::printTree(ostream& out) const {
    if (empty()) cout << "Empty Tree!" << endl;
    vector<TComp> levelOrderElements;

    queue<BinaryNode*> nodeQueue;
    nodeQueue.push(root);

    int level = 0;
    int initWidth = 128, curWidth = 0, thenWidth = 0;
    while (!nodeQueue.empty()) {
        int curQsize = nodeQueue.size();
        level++;
        initWidth = initWidth / 2;
        thenWidth = initWidth * 2 - 1;
        int numNonNull = 0;
        for (int idx = 0; idx < curQsize; ++idx) {
            curWidth = (idx == 0) ? initWidth : thenWidth;
            BinaryNode* curNode = nodeQueue.front();
            nodeQueue.pop();
            if (!curNode) {
                levelOrderElements.push_back(INT_MAX);
                out << string(curWidth + 1, ' ');
                nodeQueue.push(nullptr);
                nodeQueue.push(nullptr);
            } else {
                levelOrderElements.push_back(curNode->nodeElement);
                out << string(curWidth, ' ') 
                    << curNode->nodeElement
                    << "(" 
                    << curNode->elementCount 
                    << ")";
                nodeQueue.push(curNode->leftNode);
                nodeQueue.push(curNode->rightNode);
                numNonNull++;
            }
        }
        out << endl << endl;
        if (numNonNull == 0) break;
    }
}

template <typename TComp>
bool BST<TComp>::empty() const {
    return !root;
}

template <typename TComp>
vector<pair<TComp,int>> BST<TComp>::inOrderTraverse() const {
    vector<pair<TComp,int>> res;
    inOrderTraverse(root, res);
    return res;
}

template <typename TComp>
vector<pair<TComp,int>> BST<TComp>::preOrderTraverse() const {
    vector<pair<TComp,int>> res;
    preOrderTraverse(root, res);
    return res;
}

template <typename TComp>
vector<pair<TComp,int>> BST<TComp>::postOrderTraverse() const {
    vector<pair<TComp,int>> res;
    postOrderTraverse(root, res);
    return res;
}

template <typename TComp>
bool BST<TComp>::operator==(BST<TComp> srcBST) const {
    return isEqual(root, srcBST.root);
}
//==========================================================================
// PRIVATE METHODS
//==========================================================================
template <typename TComp>
void BST<TComp>::clear(BinaryNode*& node) {
    if (!node) return;
    clear(node->leftNode);
    clear(node->rightNode);
    delete node;
    node = nullptr;
}

template <typename TComp>
typename BST<TComp>::BinaryNode* BST<TComp>::deepCopy(BinaryNode* node) const {
    if (!node) return nullptr;
    return new BinaryNode{node->nodeElement, deepCopy(node->leftNode),
                          deepCopy(node->rightNode), node->elementCount};
}

/**
 * find the minimum element
 */
template <typename TComp>
typename BST<TComp>::BinaryNode* BST<TComp>::findMin(BinaryNode* node) const {
    // base case
    if (!node) {
        return nullptr;
    }

    // recurse logic (follows in-order traversal)
    BinaryNode* leftMinNode = findMin(node->leftNode);
    if (leftMinNode) {
        return leftMinNode;
    } else {
        return (node->elementCount) ? node : findMin(node->rightNode);
    }
}

/**
 * find the maximum element
 */
template <typename TComp>
typename BST<TComp>::BinaryNode* BST<TComp>::findMax(BinaryNode* node) const {
    // base case
    if (!node) {
        return nullptr;
    }

    // recurse logic (follows in-order traversal)
    BinaryNode* rightMaxNode = findMax(node->rightNode);
    if (rightMaxNode) {
        return rightMaxNode;
    } else {
        return (node->elementCount) ? node : findMax(node->leftNode);
    }
}

/**
 * check if element exist in current node
 */
template <typename TComp>
bool BST<TComp>::contains(const TComp& element, BinaryNode* node) const {
    if (!node) return false;
    if (element == node->nodeElement && node->elementCount) {
        return true;
    } else if (element < node->nodeElement) {
        return contains(element, node->leftNode);
    } else {
        return contains(element, node->rightNode);
    }
}
/**
 * insert an element
 */
template <typename TComp>
void BST<TComp>::insert(const TComp& element, BinaryNode*& node) {
    // base case
    if (!node) {
        node = new BinaryNode{element, nullptr, nullptr, 1};
        return;
    }

    if (element == node->nodeElement) {
        ++node->elementCount;
        return;
    }

    // isert left or right
    if (element < node->nodeElement) {
        insert(element, node->leftNode);
    } else {
        insert(element, node->rightNode);
    }
}

template <typename TComp>
void BST<TComp>::insert(TComp&& element, BinaryNode*& node) {
    // base case
    if (!node) {
        node = new BinaryNode{std::move(element), nullptr, nullptr, 1};
        return;
    }

    if (element == node->nodeElement) {
        ++node->elementCount;
        return;
    }

    // isert left or right
    if (element < node->nodeElement) {
        insert(std::move(element), node->leftNode);
    } else {
        insert(std::move(element), node->rightNode);
    }
}

/**
 * Remove an element
 */
template <typename TComp>
void BST<TComp>::erase(const TComp& element, BinaryNode*& node) {
    if (!node) return;

    if (element < node->nodeElement) {
        erase(element, node->leftNode);
    } else if (element > node->nodeElement) {
        erase(element, node->rightNode);
    } else {
        node->elementCount = std::max(0, node->elementCount-1);
    }
}
template <typename TComp>
void BST<TComp>::erase(TComp&& element, BinaryNode*& node) {
    if (!node) return;

    if (element < node->nodeElement) {
        erase(std::move(element), node->leftNode);
    } else if (element > node->nodeElement) {
        erase(std::move(element), node->rightNode);
    } else {
        node->elementCount = std::max(0, node->elementCount-1);
    }
}

template <typename TComp>
void BST<TComp>::inOrderTraverse(BinaryNode* node, vector<pair<TComp,int>>& res) const {
    if (!node) {
        return;
    }
    inOrderTraverse(node->leftNode, res);
    res.push_back(pair<TComp,int>{node->nodeElement, node->elementCount});
    inOrderTraverse(node->rightNode, res);
}

template <typename TComp>
void BST<TComp>::preOrderTraverse(BinaryNode* node, vector<pair<TComp,int>>& res) const {
    if (!node) {
        return;
    }
    res.push_back(pair<TComp,int>{node->nodeElement, node->elementCount});
    preOrderTraverse(node->leftNode, res);
    preOrderTraverse(node->rightNode, res);
}

template <typename TComp>
void BST<TComp>::postOrderTraverse(BinaryNode* node, vector<pair<TComp,int>>& res) const {
    if (!node) {
        return;
    }
    postOrderTraverse(node->leftNode, res);
    postOrderTraverse(node->rightNode, res);
    res.push_back(pair<TComp,int>{node->nodeElement, node->elementCount});
}

template<typename TComp>
bool BST<TComp>::isEqual(BinaryNode* node, BinaryNode* srcNode) const {
    if (!node || !srcNode) 
        return !srcNode && !node;
    if (node->elementCount != srcNode->elementCount ||
        node->nodeElement != srcNode->nodeElement) {
        return false;
    }
    return isEqual(node->leftNode, srcNode->leftNode)
            && isEqual(node->rightNode, srcNode->rightNode);

}

// forward type declare
template class BST<int>;
template class BST<float>;