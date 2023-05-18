#include "queue.h"

template <typename Object>
const int Queue<Object>::EXCESS_CAPACITY = 16;
//==========================================================================
// PUBLIC METHODS
//==========================================================================
/**
 * constructors
 */
template <typename Object>
Queue<Object>::Queue(int initSize)
    : arraySize{initSize + EXCESS_CAPACITY}, queueSize{0}, front{0}, back{-1} {
    objects = new Object[arraySize];
}

/**
 * copy constructor
 */
template <typename Object>
Queue<Object>::Queue(const Queue& srcQueue)
    : arraySize{srcQueue.arraySize},
      queueSize{srcQueue.queueSize},
      front{0},
      back{srcQueue.queueSize - 1} {
    objects = new Object[arraySize];
    for (int idx = 0; idx < queueSize; ++idx) {
        int srcIdx = wrap_index(idx + srcQueue.front);
        objects[idx] = srcQueue.objects[srcIdx];
    }
}

/**
 * move constructor
 */
template <typename Object>
Queue<Object>::Queue(Queue&& srcQueue)
    : objects{srcQueue.objects},
      arraySize{srcQueue.arraySize},
      queueSize{srcQueue.queueSize},
      front{srcQueue.front},
      back{srcQueue.back} {
    srcQueue.objects = nullptr;
    srcQueue.arraySize = 0;
    srcQueue.queueSize = 0;
    srcQueue.front = 0;
    srcQueue.back = -1;
}

/**
 * copy assignment
 */
template <typename Object>
Queue<Object>& Queue<Object>::operator=(const Queue& srcQueue) {
    if (srcQueue.queueSize > arraySize) {
        clear();
        arraySize = srcQueue.queueSize + EXCESS_CAPACITY;
        objects = new Object[arraySize];
    }
    queueSize = srcQueue.queueSize;
    front = 0;
    back = queueSize - 1;
    for (int idx = 0; idx < queueSize; ++idx) {
        int srcIdx = wrap_index(idx + srcQueue.front);
        objects[idx] = srcQueue.objects[srcIdx];
    }
    return *this;
}

/**
 * move assignment
 */
template <typename Object>
Queue<Object>& Queue<Object>::operator=(Queue&& srcQueue) {
    std::swap(srcQueue.queueSize, queueSize);
    std::swap(srcQueue.arraySize, arraySize);
    std::swap(srcQueue.objects, objects);
    std::swap(srcQueue.front, front);
    std::swap(srcQueue.back, back);
    return *this;
}

/**
 * Destructor
 */
template <typename Object>
Queue<Object>::~Queue() {
    clear();
}

/**
 * Enqueue
 */
template <typename Object>
void Queue<Object>::enqueue(const Object& srcElement) {
    if (queueSize == arraySize) resize();
    ++queueSize;
    back = wrap_index(back + 1);
    objects[back] = srcElement;
}

template <typename Object>
void Queue<Object>::enqueue(Object&& srcElement) {
    if (queueSize == arraySize) resize();
    ++queueSize;
    back = wrap_index(back + 1);
    objects[back] = std::move(srcElement);
}

/**
 * Dequeue
 */
template <typename Object>
Object Queue<Object>::dequeue() {
    if (queueSize == 0) {
        throw std::out_of_range("Nothing in queue");
    }
    --queueSize;
    int frontElementIdx = front;
    front = wrap_index(front + 1);
    return objects[frontElementIdx];
}

/**
 * isempty check
 */
template <typename Object>
bool Queue<Object>::isEmpty() const {
    return (queueSize == 0);
}

/**
 * make empty
 */
template <typename Object>
void Queue<Object>::makeEmpty() {
    front = 0;
    back = -1;
    queueSize = 0;
}

/**
 * all printing
 */
template <typename Object>
void Queue<Object>::print_queue(std::ostream& out) const {
    for (int idx = 0; idx < queueSize; ++idx) {
        int srcIdx = wrap_index(idx + front);
        out << objects[srcIdx] << " ";
    }
    out << std::endl;
}

template <typename Object>
void Queue<Object>::print_queue_pretty(std::ostream& out) const {
    for (int idx = 0; idx < arraySize; ++idx) {
        out << objects[idx];
        if (idx == front) out << "(F)";
        if (idx == back) out << "(B)";
        out << " ";
    }
    out << std::endl;
}

/**
 * clear
 */
template <typename Object>
void Queue<Object>::clear() {
    delete[] objects;
}

/**
 * check if equal
 */
template <typename Object>
bool Queue<Object>::operator==(const Queue& srcQueue) {
    if (srcQueue.queueSize != queueSize) {
        return false;
    }

    for (int idx = 0; idx < queueSize; ++idx) {
        int srcIdx = wrap_index(idx + srcQueue.front);
        int destIdx = wrap_index(idx + front);
        if (srcQueue.objects[srcIdx] != objects[destIdx]) {
            return false;
        }
    }
    return true;
}

/**
 * get front, back element, size
 */
template <typename Object>
const Object& Queue<Object>::getFront() const { return objects[front]; }
template <typename Object>
const Object& Queue<Object>::getBack() const { return objects[back]; }
template <typename Object>
int Queue<Object>::size() const { 
    return queueSize; 
}

//==========================================================================
// PRIVATE METHODS
//==========================================================================
template <typename Object>
int Queue<Object>::wrap_index(int idx) const {
    return (idx >= arraySize) ? idx - arraySize : idx;
}

template <typename Object>
void Queue<Object>::resize() {
    // std::cout << "resizing " << std::endl;
    int newArraySize = arraySize * 2;
    Object* newObjects = new Object[newArraySize];
    for (int idx = 0; idx < queueSize; ++idx) {
        int srcIdx = wrap_index(idx + front);
        // std::cout << srcIdx << std::endl;
        newObjects[idx] = (objects[srcIdx]);
    }
    std::swap(newObjects, objects);
    arraySize = newArraySize;
    front = 0;
    back = queueSize - 1;
    delete[] newObjects;
}

template class Queue<int>;
template class Queue<float>;