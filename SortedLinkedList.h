#ifndef __CS235_SORTED_LINKED_LIST_H_
#define __CS235_SORTED_LINKED_LIST_H_

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

/*
    This class implements a sorted doubly linked list,
    using the STL list as its underlying container.

*/
template<class T, class Comparator = std::less<T>>
class SortedLinkedList {
public:

    unsigned int size() const { return (unsigned int) linkedList.size(); }
    bool empty() const { return linkedList.empty(); }

    T& front() { return linkedList.front(); }
    T& back() { return linkedList.back(); }
    const T& front() const { return linkedList.front(); }
    const T& back() const { return linkedList.back(); }

    T& pop_front() { T& data = front(); linkedList.pop_front(); return data; }
    T& pop_back() { T& data = back(); linkedList.pop_back(); return data; }

    typedef typename std::list<T>::iterator iterator;
    typedef typename std::list<T>::const_iterator const_iterator;
    typedef typename std::list<T>::reverse_iterator reverse_iterator;
    typedef typename std::list<T>::const_reverse_iterator const_reverse_iterator;

    iterator begin() { return linkedList.begin(); }
    const_iterator begin() const { return linkedList.begin(); }
    reverse_iterator rbegin() { return linkedList.rbegin(); }
    const_reverse_iterator rbegin() const { return linkedList.rbegin(); };

    iterator end() { return linkedList.end(); }
    const_iterator end() const { return linkedList.end(); }
    reverse_iterator rend() { return linkedList.rend(); }
    const_reverse_iterator rend() const { return linkedList.rend(); };

    void display() const;
    void clear() { linkedList.clear(); }
    T& at(unsigned int pos) { auto it = linkedList.begin(); std::advance(it,pos); return *it; }
    const T& at(unsigned int pos) const { auto it = linkedList.begin(); std::advance(it,pos); return *it; }

    void insert(const T& data);
    T& remove(unsigned int pos) { auto it = linkedList.begin(); std::advance(it,pos); T& data = *it; linkedList.erase(it); return data; }
    void remove(const T& data) { linkedList.remove(data); }

    std::vector<T> toVector() const;

private:

    std::list<T> linkedList;

};

#include "SortedLinkedList.cpp"

#endif
