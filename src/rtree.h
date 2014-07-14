#ifndef RTREE_H
#define RTREE_H

#include <iostream>
#include "node.h"

template <class T> class RTree : public Node<T> {
  private:
    typedef typename Node<T>::MBR MBR;
    typedef typename Node<T>::NodePtr NodePtr;
    typedef typename Node<T>::NodeList NodeList;

    int height;
    int max_fill;
    int dimensions;

  public:
    RTree() : Node<T>(), dimensions(2) {height = 1;}
    RTree(int dim) : Node<T>(), dimensions(dim) {height = 1;}
    
    void insert(T);
    typename NodeList::iterator search(const T&);
    Node<T>* search_box(const T&);
    Node<T>* search_box(const T&, const NodePtr&);
    bool contained(const MBR rect, const T entry);
    void print_tree(); //For debugging
    void polymorph() {}
};

template <class T>
void RTree<T>::insert(T new_entry)
{
  MBR rect(3);
  rect[0] = 1;
  rect[1] = 2;
  rect[2] = 3;
      
  if (this->children.empty()) {
      this->entries.push_back(new_entry);
      if (!this->is_leaf()) {
        this->leaf = true;
      }
  } else {

    //search_ptr should point to a node
    Node<T>* search_ptr = this->search_box(new_entry); //FIX THIS
    if ( search_ptr->is_leaf() ) {
      //add entry to existing leaf node.
      search_ptr->entries.push_back(new_entry);
    } else {

      for (int i = search_ptr->level(); i < height-1; ++i) {
        search_ptr->children.push_back(std::make_pair(rect, NodePtr(new Node<T>())));
        search_ptr = search_ptr->children.back().second.get(); // Use unique_ptr get() method.
      }
      search_ptr->entries.push_back(new_entry);
      search_ptr->set_leaf(true);
    
    }
  }
  //AdjustTree();
}

template <class T>
void RTree<T>::print_tree() //For debugging
{
  std::cout << "Rect:" << std::endl;
  std::cout << "\t" << this->children.front().first[0] << std::endl;
  std::cout << "\t" << this->children.front().first[1] << std::endl;
  std::cout << "\t" << this->children.front().first[2] << std::endl;
  std::cout << std::endl;

  if (this->is_leaf()) {
    for (auto e : this->entries) {
      std::cout << e << std::endl;
    }
  }
}

template <class T>
typename RTree<T>::NodeList::iterator RTree<T>::search(const T &entry)
{
  bool diving = false;

  for (auto &p : this->children) {
    MBR rect = p.first;
    if (contained(rect, entry)) {
      diving = true;
      return search(entry, p.second);
      //break; ??
    }
  }

  if (!diving) {
    return this->children.end();
  }
}

template <class T>
Node<T>* RTree<T>::search_box(const T &entry)
{
  bool diving = false;

  if (this->is_leaf()) {
    return this;
  } else {
    for (auto &p : this->children) {
      if (contained(p.first, entry)) {
        diving = true;
        return search_box(entry, p.second);
      }
    }
    if (!diving) {
      return this;
    }
  }
}

template <class T>
Node<T>* RTree<T>::search_box(const T &entry, const NodePtr &node)
{
  bool diving = false;

  if (node->is_leaf()) {
    return this;
  } else {
    for (auto &p : node->children) {
      if (contained(p.first, entry)) {
        diving = true;
        return search_box(entry, p.second);
      }
    }
    if (!diving) {
      return node.get();
    }
  }
}

template <class T>
bool RTree<T>::contained(const MBR rect, const T entry)
{
  int i = 0;
  bool outside = false;
  
  while (i < dimensions && !outside) {
    if (i % 2) {
      outside = entry[i] > rect[i];
    } else {
      outside = entry[i] < rect[i];
    }
  }
  return !outside;
}
  

#endif
