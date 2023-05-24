#include "priority_queue.h"

#include <iostream>
using namespace std;

template <typename TComp>
const int PriorityQueue<TComp>::EXCESS_CAPACITY = 16;
/*
Improvements:
    1. decrease amount of swap
*/
/**
 * Constructing initially empty queue with reserved size
 */
template <typename TComp>
PriorityQueue<TComp>::PriorityQueue(int _reservedSize) {
    reservedSize = _reservedSize + EXCESS_CAPACITY;
    queueArray = vector<TComp>(reservedSize);
    queueSize = 0;
    defaultOffset = 0;
}

/**
 * Copy Constructor: copy from existing queueArray containing queue elements.
 */
template <typename TComp>
PriorityQueue<TComp>::PriorityQueue(const vector<TComp>& srcArray) {
    queueSize = srcArray.size();
    reservedSize = 2 * queueSize;
    queueArray = vector<TComp>(reservedSize);
    defaultOffset = 0;

    for (int idx = 0; idx < queueSize; ++idx) {
        queueArray[idx] = srcArray[idx];
    }

    heapify();
}

/**
 * Insert: insert an element to the rightmost node, percolate up
 */
template <typename TComp>
void PriorityQueue<TComp>::insert(TComp insertedElement) {
    if (queueSize == reservedSize) {
        reservedSize *= 2;
        queueArray.resize(reservedSize);
    }

    ++queueSize;
    queueArray[queueSize - 1] = insertedElement - defaultOffset;

    percolateUp(queueSize - 1);
}

/**
 * pop: delete the minimum element in the queue
 */
template <typename TComp>
TComp PriorityQueue<TComp>::pop() {
    if (queueSize == 0) throw out_of_range("Nothing else to pop!");
    TComp minElement = queueArray[0] + defaultOffset;
    queueArray[0] = queueArray[queueSize - 1];
    queueSize--;
    percolateDown(0);
    return minElement;
}

/**
 * Decrease all the keys in current heap
 */
template <typename TComp>
void PriorityQueue<TComp>::decreaseAllKeys(TComp deltaVal) {
    defaultOffset += -deltaVal;
}

/**
 * Decrease all the keys in current heap
 */
template <typename TComp>
void PriorityQueue<TComp>::increaseAllKeys(TComp deltaVal) {
    defaultOffset += deltaVal;
}

/**
 * print all elements in array style
 */
template <typename TComp>
void PriorityQueue<TComp>::print() {
    for (int idx = 0; idx < queueSize; ++idx) {
        cout << queueArray[idx] + defaultOffset << " ";
    }
    cout << endl;
}

template <typename TComp>
bool PriorityQueue<TComp>::isEqual(const std::vector<TComp>& srcArray) const {
    if (srcArray.size() != queueSize) return false;

    for (int idx = 0; idx < queueSize; ++idx) {
        if ((srcArray[idx]) 
            != (queueArray[idx] + defaultOffset)) {
            return false;
        }
    }
    return true;
}

template <typename TComp>
bool PriorityQueue<TComp>::isEmpty() const {
    return queueSize == 0;
}

/*
================================================================================================
** Private Methods:
================================================================================================
*/
/**
 * Heapify: build the heap in O(n) time
 */
template <typename TComp>
void PriorityQueue<TComp>::heapify() {
    // start from the first non-leaf node (idx=queueSize-1)
    int startIdx = ((queueSize - 1) - 1) / 2;

    // percolate up each non-leaf node
    for (int idx = startIdx; idx >= 0; --idx) {
        percolateDown(idx);
    }
}

/**
 * percolateDown: percolate down the heap
 */
template <typename TComp>
void PriorityQueue<TComp>::percolateDown(int idx) {
    // keep pushing this until heap-order property is invalid.
    bool heapValid = false;
    while (!heapValid) {
        // find minimum child index
        int leftChildIdx = idx * 2 + 1;
        int rightChildIdx = idx * 2 + 2;
        int minChildIdx = -1;

        if (rightChildIdx < queueSize) {
            // both left and right child exist
            minChildIdx =
                (queueArray[leftChildIdx] <= queueArray[rightChildIdx])
                    ? leftChildIdx
                    : rightChildIdx;
        } else if (leftChildIdx < queueSize) {
            // only left child exist
            minChildIdx = leftChildIdx;
        } else {
            // leaf node, nothing to do
            heapValid = true;
            continue;
        }

        // valid heap if element is less than minimum child
        if (queueArray[idx] <= queueArray[minChildIdx]) {
            heapValid = true;
            continue;
        }

        // percolate down
        swap(queueArray[idx], queueArray[minChildIdx]);

        // update idx
        idx = minChildIdx;
    }
}

/**
 * percolateUp: percolate up the heap
 */
template <typename TComp>
void PriorityQueue<TComp>::percolateUp(int idx) {
    bool heapValid = false;
    int parentIdx;

    while (!heapValid && idx != 0) {
        // look at parent, if parent larger percolate up
        parentIdx = (idx - 1) / 2;
        if (queueArray[idx] > queueArray[parentIdx]) {
            heapValid = true;
        } else {
            swap(queueArray[idx], queueArray[parentIdx]);
            idx = parentIdx;
        }
    }
}

/**
 * forward declare
 */
template class PriorityQueue<int>;
template class PriorityQueue<float>;
