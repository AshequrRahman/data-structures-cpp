#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

template <typename Object>
class Queue {
   public:
    // big five
    Queue(int initSize = 0);
    Queue(const Queue& srcQueue);
    Queue(Queue&& srcQueue);
    Queue& operator=(const Queue& srcQueue);
    Queue& operator=(Queue&& srcQueue);
    ~Queue();

    // public methods
    void enqueue(const Object& srcElement);
    void enqueue(Object&& srcElement);

    Object dequeue();


    bool isEmpty() const;
    void makeEmpty();

    void print_queue(std::ostream& out=std::cout) const;
    void print_queue_pretty(std::ostream& out=std::cout) const;

    bool operator==(const Queue& srcQueue);

    const Object& getFront() const;
    const Object& getBack() const;
    int size() const;

   private:
    static const int EXCESS_CAPACITY;
    int queueSize = 0;
    int arraySize = 0;
    Object* objects;
    int front;
    int back;
    int wrap_index(int idx) const;
    void resize();
    void clear();
};

#endif