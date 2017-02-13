#ifndef __CS235_SORTED_LINKED_LIST_CPP_
#define __CS235_SORTED_LINKED_LIST_CPP_

#include "SortedLinkedList.h"

template<class T, class Comparator>
void SortedLinkedList<T, Comparator>::display() const
{
    if (empty()) {
        std::cout << "(empty)" << std::endl;
        return;
    }

    auto it = linkedList.begin();
    std::cout << *it;
    for (++it; it != linkedList.end(); ++it) {
        std::cout << ", " << *it;
    }
    std::cout << std::endl;
}

template<class T, class Comparator>
void SortedLinkedList<T, Comparator>::insert(const T& data)
{
    if (empty()) {
        linkedList.push_front(data);
        return;
    }

    Comparator comparator;
    auto it = linkedList.begin();
    for (; it != linkedList.end(); ++it) {
        if (comparator(data,*it)) {
            linkedList.insert(it, data);
            break;
        }
    }
    if(it == linkedList.end()) {
        linkedList.insert(it, data);
    }
}

template<class T, class Comparator>
std::vector<T> SortedLinkedList<T, Comparator>::toVector() const
{
    std::vector<T> vec;
    auto it = linkedList.begin();
    while (it != linkedList.end()) {
        vec.push_back(*it);
        ++it;
    }
    return vec;
}

#endif
