//#include "listCustom.h"

/**
 * Implement const_iterator class
 */
template <typename Object>
class ListCustom<Object>::const_iterator {
   public:
    // zero-param constructor
    const_iterator() : nodePtr{nullptr} {}

    // dereference operator
    const Object& operator*() const { return getElement(); }

    // pre-fix increment
    const_iterator& operator++() {
        nodePtr = nodePtr->next;
        return *this;
    }

    // post-fix increment
    const_iterator& operator++(int) {
        const_iterator copyIt = *this;
        ++(*this);
        return copyIt;
    }

    // pre-fix decrement
    const_iterator& operator--() {
        nodePtr = nodePtr->prev;
        return *this;
    }

    // post-fix decrement
    const_iterator& operator--(int) {
        const_iterator copyIt = *this;
        --(*this);
        return copyIt;
    }
    
    // is equal
    bool operator==(const const_iterator& srcItr) const {
        return nodePtr == srcItr.nodePtr;
    }

    // is not equal
    bool operator!=(const const_iterator& srcItr) const {
        return !(*this == srcItr);
    }

   protected:
    Node* nodePtr;
    // hidden constructor, accessible by parent and child class
    const_iterator(Node* srcNodePtr) : nodePtr{srcNodePtr} {}

    // private method to dereference element pointed by it
    Object& getElement() const { return nodePtr->element; }

    friend class ListCustom<Object>;
};

/**
 * Implement iterator class
 */
template <typename Object>
class ListCustom<Object>::iterator : public ListCustom<Object>::const_iterator {
   public:
    // zero-param constructor
    iterator() {}
    // dereference operator
    Object& operator*() { return const_iterator::getElement(); }
    const Object& operator*() const { return const_iterator::operator*(); }

    // increment
    iterator operator++() {
        this->nodePtr = this->nodePtr->next;
        return *this;
    }
    iterator operator++(int) {
        iterator copyIt = *this;
        ++(*this);
        return copyIt;
    }

    // pre-fix decrement
    iterator& operator--() {
        this->nodePtr = this->nodePtr->prev;
        return *this;
    }

    // post-fix decrement
    iterator& operator--(int) {
        iterator copyIt = *this;
        --(*this);
        return copyIt;
    }

   protected:
    iterator(Node* srcNodePtr) : const_iterator{srcNodePtr} {};
    friend class ListCustom<Object>;
};

/**
 * Node definition
 */
template <typename Object>
struct ListCustom<Object>::Node {
    Object element;
    Node* next;
    Node* prev;

    // constructors
    Node(const Object& srcElement = Object{}, Node* srcNext = nullptr,
         Node* srcPrev = nullptr)
        : element{srcElement}, next{srcNext}, prev{srcPrev} {}
    Node(Object&& srcElement, Node* srcNext = nullptr, Node* srcPrev = nullptr)
        : element{std::move(srcElement)}, next{srcNext}, prev{srcPrev} {}
};

/**
 * constructor
 */
template <typename Object>
ListCustom<Object>::ListCustom() {
    createSentinels();
}

/**
 * copy constructor
 */
template <typename Object>
ListCustom<Object>::ListCustom(const ListCustom& srcList) {
    createSentinels();
    deepCopy(srcList);
}

/**
 * move constructor
 */
template <typename Object>
ListCustom<Object>::ListCustom(ListCustom&& srcList)
    : head{srcList.head}, tail{srcList.tail}, listSize{srcList.listSize} {
    srcList.head = nullptr;
    srcList.tail = nullptr;
    srcList.listSize = 0;
}

/**
 * copy assignment
 */
template <typename Object>
ListCustom<Object>& ListCustom<Object>::operator=(const ListCustom& srcList) {
    ListCustom cpList = srcList;
    std::swap(cpList, *this);
    return *this;
}

/**
 * move assignment
 */
template <typename Object>
ListCustom<Object>& ListCustom<Object>::operator=(ListCustom&& srcList) {
    // createSentinels();
    std::swap(head, srcList.head);
    std::swap(tail, srcList.tail);
    std::swap(listSize, srcList.listSize);
    return *this;
}

/**
 * destructor
 */
template <typename Object>
ListCustom<Object>::~ListCustom() {
    clear();
    delete head;
    delete tail;
}

/**
 * clear
 */
template <typename Object>
void ListCustom<Object>::clear() {
    while (listSize != 0) {
        erase_front();
    }
    // delete head;
    // delete tail;
}

/**
 * all insert methods
 */
template <typename Object>
void ListCustom<Object>::insert(const Object& srcElement, int idx) {
    if (idx > listSize) return;
    iterator nodeIter = begin();
    for (int i = 0; i != idx; ++i, nodeIter++) {
    }
    insert(srcElement, nodeIter);
}

template <typename Object>
void ListCustom<Object>::insert(const Object& srcElement, iterator nodeIter) {
    Node* newNode =
        new Node{srcElement, nodeIter.nodePtr, nodeIter.nodePtr->prev};
    nodeIter.nodePtr->prev = newNode;
    newNode->prev->next = newNode;
    listSize++;
}

template <typename Object>
void ListCustom<Object>::insert(Object&& srcElement, int idx) {
    if (idx > listSize) return;
    iterator nodeIter = begin();
    for (int i = 0; i != idx; ++i, nodeIter++) {
    }
    insert(std::move(srcElement), nodeIter);
}

template <typename Object>
void ListCustom<Object>::insert(Object&& srcElement, iterator nodeIter) {
    Node* newNode = new Node{std::move(srcElement), nodeIter.nodePtr,
                             nodeIter.nodePtr->prev};
    nodeIter.nodePtr->prev = newNode;
    newNode->prev->next = newNode;
    listSize++;
}

template <typename Object>
void ListCustom<Object>::insert_front(const Object& srcElement) {
    insert(srcElement, begin());
}
template <typename Object>
void ListCustom<Object>::insert_back(const Object& srcElement) {
    insert(srcElement, end());
}
template <typename Object>
void ListCustom<Object>::insert_front(Object&& srcElement) {
    insert(std::move(srcElement), begin());
}
template <typename Object>
void ListCustom<Object>::insert_back(Object&& srcElement) {
    insert(std::move(srcElement), end());
}

/**
 * all erase method
 */
template <typename Object>
void ListCustom<Object>::erase(iterator nodeIter) {
    nodeIter.nodePtr->prev->next = nodeIter.nodePtr->next;
    nodeIter.nodePtr->next->prev = nodeIter.nodePtr->prev;
    delete nodeIter.nodePtr;
    listSize--;
}

template <typename Object>
void ListCustom<Object>::erase(iterator nodeIterFrom, iterator nodeIterTo) {
    for (auto it = nodeIterFrom; it != nodeIterTo; ++it) {
        erase(it);
    }
}

template <typename Object>
void ListCustom<Object>::erase(int idx) {
    iterator nodeIter = begin();
    for (int i = 0; i != idx; ++i, nodeIter++) {
    }
    erase(nodeIter);
}

template <typename Object>
void ListCustom<Object>::erase_front() {
    iterator nodeIter = begin();
    erase(nodeIter);
}

template <typename Object>
void ListCustom<Object>::erase_back() {
    iterator nodeIter = iterator{tail->prev};
    erase(nodeIter);
}

/**
 * indexing operator
 */
template <typename Object>
const Object& ListCustom<Object>::operator[](int idx) const {
    // std::cout << "constant indexing called here " << std::endl;
    const_iterator nodeIter = begin();
    for (int i = 0; i != idx; ++i, nodeIter++) {
    }
    return nodeIter.getElement();
}
template <typename Object>
Object& ListCustom<Object>::operator[](int idx) {
    // std::cout << "non-constant indexing called here " << std::endl;
    iterator nodeIter = begin();
    for (int i = 0; i != idx; ++i, nodeIter++) {
    }
    return nodeIter.getElement();
}

/**
 * iterator begin end method
 */

template <typename Object>
typename ListCustom<Object>::iterator ListCustom<Object>::begin() {
    return iterator{head->next};
}
template <typename Object>
typename ListCustom<Object>::const_iterator ListCustom<Object>::begin() const {
    return const_iterator{head->next};
}
template <typename Object>
typename ListCustom<Object>::iterator ListCustom<Object>::end() {
    return iterator{tail};
}
template <typename Object>
typename ListCustom<Object>::const_iterator ListCustom<Object>::end() const {
    return const_iterator{tail};
}

/**
 * for printing
 */
template <typename Object>
std::ostream& operator<<(std::ostream& out, const ListCustom<Object>& srcList) {
    srcList.print_list(out);
    return out;
}

template <typename Object>
void ListCustom<Object>::print_list(std::ostream& out) const {
    if (!head || !tail) {
        out << "list is delted" << std::endl;
        return;
    }

    Node* nodeIter = head->next;
    while (nodeIter != tail) {
        out << nodeIter->element << " ";
        nodeIter = nodeIter->next;
    }
    out << std::endl;
}

//===================================================================
// Private methods
//===================================================================
/**
 * deepcopy
 */
template <typename Object>
void ListCustom<Object>::deepCopy(const ListCustom& srcList) {
    Node* srcNodeIter = srcList.head->next;
    while (srcNodeIter != srcList.tail) {
        insert_back(srcNodeIter->element);
        srcNodeIter = srcNodeIter->next;
    }
}

template <typename Object>
void ListCustom<Object>::createSentinels() {
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}

//template class ListCustom<int>;
//template class ListCustom<float>;