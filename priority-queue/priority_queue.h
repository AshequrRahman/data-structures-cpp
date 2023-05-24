#ifndef PriorityQueue_H
#define PriorityQueue_H

#include <vector>

/**
 * Class for priority queue data structure.
 * Implemented using binary heap. 
 * Supports decreasing/increasing all keys in O(1) time
 */
template <typename TComp>
class PriorityQueue {
    public:
        explicit PriorityQueue(int reservedSize = 0);
        explicit PriorityQueue(const std::vector<TComp>& initArray);
        void insert(TComp insertedElement);
        TComp pop();
        void decreaseAllKeys(TComp deltaVal);
        void increaseAllKeys(TComp deltaVal);
        void print();

        bool isEqual(const std::vector<TComp>& srcArray) const;
        bool isEmpty() const;

       private:
        static const int EXCESS_CAPACITY;
        int reservedSize;
        int queueSize;
        TComp defaultOffset;
        std::vector<TComp> queueArray;
        void heapify();
        void percolateDown(int idx);
        void percolateUp(int idx);
        //void increaseReservedSize();
};

#endif
