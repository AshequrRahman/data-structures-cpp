#ifndef VECTOR_CUSTOM_H
#define VECTOR_CUSTOM_H

#include <iostream>
template <typename Object>
class VectorCustom {
   public:
    // Big five

    // constructor
    explicit VectorCustom(int initialSize = 0);
    // copy constructor
    VectorCustom(const VectorCustom& srcVector);
    // move constructor
    VectorCustom(VectorCustom&& srcVector);
    // copy assignment
    VectorCustom& operator=(const VectorCustom& srcVector);
    // move assignment
    VectorCustom& operator=(VectorCustom&& srcVector);
    // destructor
    ~VectorCustom();

    // public methods
    void push_back(const Object& element);
    void push_back(Object&& element);

    Object pop_back();

    const Object& operator[](int idx) const;
    Object& operator[](int idx);

    typedef Object* iterator;
    typedef const Object* const_iterator;

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    void print_vector(std::ostream& out=std::cout) const;
    bool operator==(const VectorCustom& srcVec) const;

    bool isEmpty() const;

   private:
    static const int EXCESS_CAPACITY;
    Object* objects;
    int arraySize;
    int vectorSize;

    void clear();
    void resize();
};

#endif