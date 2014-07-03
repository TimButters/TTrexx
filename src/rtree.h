#ifndef RTREE_H
#define RTREE_H

#include <iostream>
#include "tree.h"

template <class T> class RTree : public Tree<T> {
  public:
    RTree() : Tree<T>() {}
    T search() {} // Clearly needs implementing, just needs setting to make class concrete.
    void del(T) {}
    void condense() {}
    void adjust() {}
    
    void insert(T entry);
    void print_tree(); //For debugging
};

template <class T>
void RTree<T>::insert(T entry)
{
  this->children.push_back(std::make_tuple(1.0,2.0,3.0, entry));
}

template <class T>
void RTree<T>::print_tree() //For debugging
{
  for (auto &each : this->children) {
    std::cout << std::get<0>(each) << std::endl;
    std::cout << std::get<1>(each) << std::endl;
    std::cout << std::get<2>(each) << std::endl;
    std::cout << std::get<3>(each) << std::endl;
  }
}

#endif
