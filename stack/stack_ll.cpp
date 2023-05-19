#include "stack_ll.h"

/**
 * zero-parmeter constructor
 */
template <typename Object>
StackLL<Object>::StackLL() : headPointer{nullptr}, stackSize{0} {}

/**
 * copy constructor
 */
template <typename Object>
StackLL<Object>::StackLL(const StackLL& srcStack)
    : stackSize{srcStack.stackSize} {
    headPointer = deepCopy(srcStack.headPointer);
}

/**
 * move constructor
 */
template <typename Object>
StackLL<Object>::StackLL(StackLL&& srcStack)
    : headPointer{srcStack.headPointer}, stackSize{srcStack.stackSize} {
    srcStack.headPointer = nullptr;
    srcStack.stackSize = 0;
}

/**
 * copy assignment
 */
template <typename Object>
StackLL<Object>& StackLL<Object>::operator=(const StackLL& srcStack) {
    if (this != &srcStack) {
        clear();
        headPointer = deepCopy(srcStack.headPointer);
        stackSize = srcStack.stackSize;
    }
    return *this;
}

/**
 * move assignment
 */
template <typename Object>
StackLL<Object>& StackLL<Object>::operator=(StackLL&& srcStack) {
    std::swap(headPointer, srcStack.headPointer);
    std::swap(stackSize, srcStack.stackSize);
    return *this;
}

/**
 * Destructor
 */
template <typename Object>
StackLL<Object>::~StackLL() {
    clear();
}

/**
 * clear the current stack
 */
template <typename Object>
void StackLL<Object>::clear() {
    clear(headPointer);
}

/**
 * return the front element/ top of the stack
 */
template <typename Object>
const Object& StackLL<Object>::front() const {
    if (isEmpty()) {
        throw std::out_of_range("Stack Underflow");
        ;
    }
    return headPointer->element;
}

/**
 * pop the front element
 */
template <typename Object>
Object StackLL<Object>::pop() {
    if (isEmpty()) {
        throw std::out_of_range("Stack Underflow");
        ;
    }

    // keep a copy of headpointer
    ListNode* nodeToBeDeleted = headPointer;
    headPointer = headPointer->nextNode;
    Object poppedElement = nodeToBeDeleted->element;
    delete nodeToBeDeleted;
    --stackSize;
    return poppedElement;
}

/**
 * push into front
 */
template <typename Object>
void StackLL<Object>::push(const Object& srcElement) {
    ListNode* newNode = new ListNode{srcElement, headPointer};
    headPointer = newNode;
    ++stackSize;
}
template <typename Object>
void StackLL<Object>::push(Object&& srcElement) {
    ListNode* newNode = new ListNode{std::move(srcElement), headPointer};
    headPointer = newNode;
    ++stackSize;
}

/**
 * check if empty
 */
template <typename Object>
bool StackLL<Object>::isEmpty() const {
    return !headPointer;
}

template <typename Object>
void StackLL<Object>::printStack(std::ostream& out) const {
    if (isEmpty()) {
        out << "Empty Stack!" << std::endl;
    }

    ListNode* curPointer = headPointer;
    while (curPointer) {
        out << curPointer->element << " ";
        curPointer = curPointer->nextNode;
    }
    out << std::endl;
}

template <typename Object>
int StackLL<Object>::size() const {
    return stackSize;
}

template <typename Object>
bool StackLL<Object>::operator==(const StackLL& srcStack) const {
    if (stackSize != srcStack.stackSize) return false;
    ListNode* curPointer = headPointer;
    ListNode* srcPointer = srcStack.headPointer;
    while (curPointer && srcPointer) {
        if (curPointer->element != srcPointer->element) return false;
        curPointer = curPointer->nextNode;
        srcPointer = srcPointer->nextNode;
    }

    return true;
}

//==========================================================================
// PRIVATE METHODS
//==========================================================================
template <typename Object>
void StackLL<Object>::clear(ListNode*& node) {
    // base case
    if (!node) return;

    clear(node->nextNode);
    delete node;
    node = nullptr;
}

template <typename Object>
typename StackLL<Object>::ListNode* StackLL<Object>::deepCopy(ListNode* node) {
    // base case
    if (!node) return nullptr;

    return new ListNode{node->element, deepCopy(node->nextNode)};
}

// forward type declare
template class StackLL<int>;
template class StackLL<float>;