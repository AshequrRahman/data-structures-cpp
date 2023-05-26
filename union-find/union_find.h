#ifndef UnionFind_H
#define UnionFind_H

#include <iostream>
#include <vector>
#include <map>
using namespace std;
/**
 * Class for implementing union find data structure.
 * The class allows path compression and union-by-size strategies.
 * Assumptions:
 *      1. The elements must be of same type
 */
template <typename TComp>
class UnionFind {
    public:
        // Big-five
        UnionFind(const vector<TComp>& elements);
        UnionFind(vector<TComp>&& elements);
        UnionFind(const UnionFind<TComp>& srcUF);
        UnionFind(UnionFind<TComp>&& srcUF);
        UnionFind& operator=(const UnionFind<TComp>& srcUF);
        UnionFind& operator=(UnionFind<TComp>&& srcUF);
        ~UnionFind() = default;

        // accessor version of finding root element and index
        //const TComp& findRootOfElement(const TComp& x) const;
        int findRootIdxOfElement(const TComp& x) const;

        // mutator version of finding root element and index (allows path compression)
        //const TComp& findRootOfElement(const TComp& x);
        int findRootIdxOfElement(const TComp& x);

        // connect two component
        void connect(const TComp& elem1, const TComp& elem2);

        // check if connected
        bool isConnected(const TComp& elem1, const TComp& elem2);

        // add an element
        void addElement(const TComp& elem);

        // print the array describing roots and size
        void printParentsAndRootSize();

        // for testing
        vector<int> getParentVector() const;
        unordered_map<TComp, int> getMap() const;

        bool operator==(const UnionFind<TComp>& srcUF);

       private:
        vector<int> parentsAndRootSize;
        unordered_map<TComp, int> mapElToIdx;
        int numElements;
        int find(int x);
};

#endif