#ifndef STACK_LL_H
#define STACK_LL_H
#include <iostream>
template <typename Object>
class StackLL {
   public:
    // Big five
    StackLL();
    StackLL(const StackLL& srcStack);
    StackLL(StackLL&& srcStack);
    StackLL& operator=(const StackLL& srcStack);
    StackLL& operator=(StackLL&& srcStack);
    ~StackLL();

    // ADT public methods
    void push(const Object& elem);
    void push(Object&& elem);

    const Object& front() const;

    Object pop();

    void clear();

    bool isEmpty() const;

    void printStack(std::ostream& out = std::cout) const;

    int size() const;

    bool operator==(const StackLL& srcStack) const;

   private:
    struct ListNode {
        Object element;
        ListNode* nextNode;

        ListNode(const Object& element, ListNode* node)
            : element{element}, nextNode{node} {};

        ListNode(Object&& element, ListNode* node)
            : element{std::move(element)}, nextNode{node} {};
    };

    int stackSize;
    ListNode* headPointer;

    void clear(ListNode*& node);
    ListNode* deepCopy(ListNode* node);
};

#endif