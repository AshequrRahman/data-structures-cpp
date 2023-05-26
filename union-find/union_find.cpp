#include "union_find.h"

/**
 *  Copy Constructor
 */
template <typename TComp>
UnionFind<TComp>::UnionFind(const vector<TComp>& elements) {
    int count = 0;
    for (auto& el : elements) {
        if (mapElToIdx.find(el) == mapElToIdx.end()) {
            mapElToIdx[el] = count;
            ++count;
        }
    }
    parentsAndRootSize = vector<int>(count, -1);
    numElements = count;
}
template <typename TComp>
UnionFind<TComp>::UnionFind(const UnionFind<TComp>& srcUF)
    : numElements{srcUF.numElements},
      mapElToIdx{srcUF.mapElToIdx},
      parentsAndRootSize{srcUF.parentsAndRootSize} {}

/**
 *  Move Constructor
 */
template <typename TComp>
UnionFind<TComp>::UnionFind(vector<TComp>&& elements) {
    vector<TComp> elementsCp{std::move(elements)};
    int count = 0;
    for (auto& el : elementsCp) {
        if (mapElToIdx.find(el) == mapElToIdx.end()) {
            mapElToIdx[el] = count;
            ++count;
        }
    }
    parentsAndRootSize = vector<int>(count, -1);
    numElements = count;
}
template <typename TComp>
UnionFind<TComp>::UnionFind(UnionFind<TComp>&& srcUF)
    : numElements{srcUF.numElements},
      mapElToIdx{std::move(srcUF.mapElToIdx)},
      parentsAndRootSize{std::move(srcUF.parentsAndRootSize)} {
    srcUF.parentsAndRootSize = {};
    srcUF.mapElToIdx = {};
}

/**
 * copy assignment
 */
template <typename TComp>
UnionFind<TComp>& UnionFind<TComp>::operator=(const UnionFind<TComp>& srcUF) {
    if (&srcUF != this) {
        mapElToIdx = srcUF.mapElToIdx;
        parentsAndRootSize = srcUF.parentsAndRootSize;
        numElements = srcUF.numElements;
    }
    return *this;
}

/**
 * move assignment
 */
template <typename TComp>
UnionFind<TComp>& UnionFind<TComp>::operator=(UnionFind<TComp>&& srcUF) {
    std::swap(numElements, srcUF.numElements);
    std::swap(parentsAndRootSize, srcUF.parentsAndRootSize);
    std::swap(mapElToIdx, srcUF.mapElToIdx);
    return *this;
}

/**
 * find algorithm
 * allows path compression in each find call
 */
template <typename TComp>
int UnionFind<TComp>::findRootIdxOfElement(const TComp& x) {
    return find(mapElToIdx[x]);
}

/**
 * connect algorhim
 * Unionize two groups containing the two input elements
 * When doing union, root of the smaller tree becomes the children of the root
 * of larger tree.
 */
template <typename TComp>
void UnionFind<TComp>::connect(const TComp& elem1, const TComp& elem2) {
    int root1 = findRootIdxOfElement(elem1);
    int root2 = findRootIdxOfElement(elem2);

    if (root1 == root2) return;

    if (parentsAndRootSize[root1] <= parentsAndRootSize[root2]) {
        // connect small-sized root2
        parentsAndRootSize[root1] += parentsAndRootSize[root2];
        parentsAndRootSize[root2] = root1;
    } else {
        // connect small-sized root1
        parentsAndRootSize[root2] += parentsAndRootSize[root1];
        parentsAndRootSize[root1] = root2;
    }
}

/**
 * return true if two elements are in the same set
 */
template <typename TComp>
bool UnionFind<TComp>::isConnected(const TComp& elem1, const TComp& elem2) {
    return findRootIdxOfElement(elem1) == findRootIdxOfElement(elem2);
}

/**
 * add new element
 */
template <typename TComp>
void UnionFind<TComp>::addElement(const TComp& element) {
    if (mapElToIdx.find(element) != mapElToIdx.end()) return;
    mapElToIdx[element] = numElements;
    parentsAndRootSize.push_back(-1);
    ++numElements;
}

/**
 * Print the parentsAndRootSize array
 */
template <typename TComp>
void UnionFind<TComp>::printParentsAndRootSize() {
    for (auto& elem : parentsAndRootSize) cout << elem << " ";
    cout << endl;
}

template <typename TComp>
bool UnionFind<TComp>::operator==(const UnionFind<TComp>& srcUF) {
    return (srcUF.numElements == numElements) &&
           (srcUF.mapElToIdx == mapElToIdx) &&
           (srcUF.parentsAndRootSize == parentsAndRootSize);
}

/**
 * find algo
 */
template <typename TComp>
int UnionFind<TComp>::find(int x) {
    if (parentsAndRootSize[x] < 0) {
        return x;
    } else {
        return parentsAndRootSize[x] = find(parentsAndRootSize[x]);
    }
}

template <typename TComp>
vector<int> UnionFind<TComp>::getParentVector() const {
    return parentsAndRootSize;
}
template <typename TComp>
unordered_map<TComp, int> UnionFind<TComp>::getMap() const {
    return mapElToIdx;
}

/**
 * forward declare
 */
template class UnionFind<int>;
template class UnionFind<float>;
template class UnionFind<string>;