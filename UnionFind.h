#ifndef _UNION_FIND_H
#define _UNION_FIND_H

#include "DynamicArray.h"


template<class T>
struct UnionFindNode {
    int current_parent;
    T data;
};


template<class T>
class UnionFind {
    int count;
    Array<int> sizes;
    Array<UnionFindNode<T>* > nodes;

public:

    UnionFind() : count(0) {}      //Alocates a dynamic array of size 10.
    ~UnionFind();
    void makeSet();             //Uses default constructor of type T.
    int find(int index);
    void Union(int index1, int index2);

    UnionFindNode<T>* getElement(int index);
    int getElementCount();

};



template<class T>
UnionFind<T>::~UnionFind()
{
    for (int i = 0; i < count; i++) {
        delete nodes.get(i);
    }
}


template<class T>
void UnionFind<T>::makeSet()
{
    UnionFindNode<T>* new_elem = new UnionFindNode<T>;
    new_elem->current_parent = count;

    nodes.set(count, new_elem);
    sizes.set(count, 1);
    count++;
}


template<class T>
int UnionFind<T>::find(int index)
{
    UnionFindNode<T>* ptr = nodes.get(index);

    if (ptr->current_parent == index) {
        return index;
    }
    else {
        ptr->current_parent = find(ptr->current_parent);
    }

    return ptr->current_parent;
}


template<class T>
void UnionFind<T>::Union(int index1, int index2)
{
    int parent1 = find(index1), parent2 = find(index2);
    UnionFindNode<T>* ptr1 = nodes.get(parent1), *ptr2 = nodes.get(parent2);

    if (parent1 == parent2) return;

    if (sizes.get(parent1) < sizes.get(parent2)) {
        ptr1->current_parent = parent2;
        ptr2->data = ptr1->data + ptr2->data;  //type T operator+

        sizes.set(parent2,sizes.get(parent1) + sizes.get(parent2));

    }
    else {
        ptr2->current_parent = parent1;
        ptr1->data = ptr1->data + ptr2->data;  //type T operator+

        sizes.set(parent1, sizes.get(parent1) + sizes.get(parent2));
    }
}


template<class T>
UnionFindNode<T>* UnionFind<T>::getElement(int index)
{
    return (index < 0 || index >= count) ? nullptr : nodes.get(find(index));
}


template<class T>
int UnionFind<T>::getElementCount()
{
    return count;
}


#endif