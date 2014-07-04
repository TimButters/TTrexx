#ifndef RTREE_H
#define RTREE_H

#include <iostream>
#include "node.h"

template <class T> class RTree : public Node<T> {
  private:
    typedef typename Node<T>::MBR MBR;
    typedef typename Node<T>::NodePtr NodePtr;
  public:
    RTree() : Node<T>() {}
    /*T search() {}
    void del(T) {}
    void condense() {}
    void adjust() {}*/
    
    void insert(T entry);
    void print_tree(); //For debugging
};

template <class T>
void RTree<T>::insert(T new_entry)
{
  MBR rect(3);
  rect[0] = 1;
  rect[1] = 2;
  rect[2] = 3;

  this->children.push_back(std::make_pair(rect, std::unique_ptr<Node<T>>(new Node<T>(new_entry))));
}

template <class T>
void RTree<T>::print_tree() //For debugging
{
  std::cout << "Rect:" << std::endl;
  std::cout << "\t" << this->children.front().first[0] << std::endl;
  std::cout << "\t" << this->children.front().first[1] << std::endl;
  std::cout << "\t" << this->children.front().first[2] << std::endl;
  std::cout << std::endl;
 
  if (this->children.front().second->is_leaf()) {
    std::cout << "Entry: " << this->children.front().second->get_entry() << std::endl;
  }
}

#endif
