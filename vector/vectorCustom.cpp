#include "vectorCustom.h"

template <typename Object>
const int VectorCustom<Object>::EXCESS_CAPACITY = 16;

/**
 * constructor
 */
template <typename Object>
VectorCustom<Object>::VectorCustom(int initialSize) {
    arraySize = initialSize + EXCESS_CAPACITY;
    objects = new Object[arraySize];
    vectorSize = 0;
}

/**
 * copy constructor
 */
template <typename Object>
VectorCustom<Object>::VectorCustom(const VectorCustom& srcVector) {
    arraySize = srcVector.vectorSize + EXCESS_CAPACITY;
    objects = new Object[arraySize];
    vectorSize = srcVector.vectorSize;

    for (int idx = 0; idx < srcVector.vectorSize; ++idx) {
        objects[idx] = srcVector.objects[idx];
    }
}

/**
 * move constructor
 */
template <typename Object>
VectorCustom<Object>::VectorCustom(VectorCustom&& srcVector)
    : objects{srcVector.objects},
      arraySize{srcVector.arraySize},
      vectorSize{srcVector.vectorSize} {
    srcVector.objects = nullptr;
    srcVector.arraySize = 0;
    srcVector.vectorSize = 0;
}

/**
 * copy assignment
 */
template <typename Object>
VectorCustom<Object>& VectorCustom<Object>::operator=(
    const VectorCustom& srcVector) {
    if (arraySize < srcVector.vectorSize) {
        clear();
        arraySize = srcVector.vectorSize + EXCESS_CAPACITY;
        objects = new Object[arraySize];
    }

    vectorSize = srcVector.vectorSize;
    for (int idx = 0; idx < srcVector.vectorSize; ++idx) {
        objects[idx] = srcVector.objects[idx];
    }

    return *this;
}

/**
 * move assignment
 */
template <typename Object>
VectorCustom<Object>& VectorCustom<Object>::operator=(
    VectorCustom&& srcVector) {
    std::swap(arraySize, srcVector.arraySize);
    std::swap(vectorSize, srcVector.vectorSize);
    std::swap(objects, srcVector.objects);
    return *this;
}

/**
 * destructor
 */
template <typename Object>
VectorCustom<Object>::~VectorCustom() {
    clear();
}

/**
 * push_back
 */
template <typename Object>
void VectorCustom<Object>::push_back(const Object& element) {
    if (arraySize == vectorSize) {
        resize();
    }
    objects[vectorSize++] = element;
}
template <typename Object>
void VectorCustom<Object>::push_back(Object&& element) {
    if (arraySize == vectorSize) {
        resize();
    }
    objects[vectorSize++] = std::move(element);
}

/**
 * pop_back
 */
template <typename Object>
Object VectorCustom<Object>::pop_back() {
    if (vectorSize == 0) {
        throw std::out_of_range("Index out of range");
    }
    --vectorSize;
    return objects[vectorSize];
}

/**
 * indexing
 */
template <typename Object>
const Object& VectorCustom<Object>::operator[](int idx) const {
    if (idx >= vectorSize) {
        throw std::out_of_range("Index out of range");
        ;
    }
    return objects[idx];
}
template <typename Object>
Object& VectorCustom<Object>::operator[](int idx) {
    if (idx >= vectorSize) {
        throw std::out_of_range("Index out of range");
        ;
    }
    return objects[idx];
}

/**
 * iterators!!
 */

template <typename Object>
typename VectorCustom<Object>::iterator VectorCustom<Object>::begin() {
    return &objects[0];
}
template <typename Object>
typename VectorCustom<Object>::const_iterator VectorCustom<Object>::begin()
    const {
    return &objects[0];
}

template <typename Object>
typename VectorCustom<Object>::iterator VectorCustom<Object>::end() {
    return &objects[vectorSize];
}
template <typename Object>
typename VectorCustom<Object>::const_iterator VectorCustom<Object>::end()
    const {
    return &objects[vectorSize];
}

/**
 * printing
 */
template <typename Object>
void VectorCustom<Object>::print_vector(std::ostream& out) const {
    if (vectorSize == 0) {
        out << "Empty vector!" << std::endl;
    }

    for (int idx = 0; idx < vectorSize; ++idx) {
        out << objects[idx] << " ";
    }
    out << std::endl;
}

template <typename Object>
bool VectorCustom<Object>::operator==(const VectorCustom& srcVec) const {
    if (srcVec.vectorSize != vectorSize) return false;
    for (int idx = 0; idx < vectorSize; ++idx) {
        if (objects[idx] != srcVec.objects[idx]) {
            return false;
        }
    }
    return true;
}

template <typename Object>
bool VectorCustom<Object>::isEmpty() const {
    return vectorSize == 0;
}

/**================================================================
 * Private methods
 ==================================================================*/
/**
 * clear the objects array
 */
template <typename Object>
void VectorCustom<Object>::clear() {
    delete[] objects;
}

/**
 * resize the objects array
 */
template <typename Object>
void VectorCustom<Object>::resize() {
    Object* copyObjects = new Object[2 * arraySize];
    for (int idx = 0; idx < vectorSize; ++idx) {
        copyObjects[idx] = objects[idx];
    }
    clear();
    objects = copyObjects;
    arraySize *= 2;
}

// forward type declare
template class VectorCustom<int>;
template class VectorCustom<float>;