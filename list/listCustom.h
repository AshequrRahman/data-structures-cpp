#ifndef LIST_CUSTOM_H
#define LIST_CUSTOM_H

#include <iostream>


template <typename Object>
class ListCustom {
   public:
    // nested iterator class
    class const_iterator;
    class iterator;

    // big five
    ListCustom();
    ListCustom(const ListCustom& srcList);
    ListCustom(ListCustom&& srcList);
    ListCustom& operator=(const ListCustom& srcList);
    ListCustom& operator=(ListCustom&& srcList);
    ~ListCustom();

    // public methods
    void insert(const Object& element, int idx);
    void insert(Object&& element, int idx);
    void insert(const Object& element, iterator it);
    void insert(Object&& element, iterator it);

    void insert_front(const Object& element);
    void insert_front(Object&& element);

    void insert_back(const Object& element);
    void insert_back(Object&& element);

    void erase(int idx);
    void erase(iterator it);
    void erase(iterator it_from, iterator it_to);
    void erase_front();
    void erase_back();

    const Object& operator[](int idx) const;

    Object& operator[](int idx);

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    void clear();

    void print_list(std::ostream& out = std::cout) const;

   private:
    struct Node;
    Node* head;
    Node* tail;
    void deepCopy(const ListCustom& srcList);
    int listSize = 0;
    void createSentinels();
};

template <typename Object>
std::ostream& operator<<(std::ostream& out, const ListCustom<Object>& srcList);

#include "listCustom.cpp"

#endif
