#ifndef RTREE_H
#define RTREE_H

#include <iostream>
#include <limits>
#include "node.h"

template <class T> class RTree : public Node<T> {
  private:
    typedef typename Node<T>::MBR MBR;
    typedef typename Node<T>::NodePtr NodePtr;
    typedef typename Node<T>::NodeList NodeList;

    int height;
    int max_fill=3;
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
    //void polymorph() {}
};

template <class T>
void RTree<T>::insert(T new_entry)
{
  if (this->children.empty()) {
      this->entries.push_back(new_entry);
      if (!this->is_leaf()) {
        this->leaf = true;
      }
      if (this->entries.size() > max_fill) {
        this->children.push_back(this->split(this));
        this->children.push_back(std::make_pair(this->find_mbr(this->entries), NodePtr(new Node<T>(this->entries, this))));
        this->entries.clear();
        this->leaf = false;
      }
  } else {
    Node<T>* search_ptr = this->search_box(new_entry);
    if ( search_ptr->is_leaf() ) {

      search_ptr->entries.push_back(new_entry);
      // Split Node if it overflows.
      if (search_ptr->entries.size() > max_fill) {
        search_ptr->up()->children.push_back(search_ptr->split(search_ptr->up(), true));
        //MBR for entry in children to this node needs re-calculating.
        //Propogate change up tree.
      }

    } else {
      // if (next node is leaf) {
      std::list<T> points;
      typename NodeList::iterator iter, min_expansion;
      double best_fit = std::numeric_limits<double>::infinity();
      for (iter = search_ptr->children.begin(); iter != search_ptr->children.end(); ++iter) {
        MBR curr_mbr = iter->first;
        points = iter->second->entries;
        points.push_back(new_entry);
        MBR new_mbr = this->find_mbr(points);
        if (new_mbr - curr_mbr < best_fit) {
          best_fit = new_mbr - curr_mbr;
          min_expansion = iter;
        }
      }
      min_expansion->second->entries.push_back(new_entry);
      min_expansion->first = this->find_mbr(min_expansion->second->entries);
      //Split Node if it overflows.
      if (min_expansion->second->entries.size() > max_fill) {
        this->children.push_back(min_expansion->second->split(this));
        min_expansion->first = this->find_mbr(min_expansion->second->entries);
        //Propogate changes up tree
      }
      //}
    }
  }
  //AdjustTree();
}

template <class T>
void RTree<T>::print_tree() //For debugging
{
  if (!this->is_leaf()) {
    for (const auto &c : this->children) {
      std::cout << "Rect:" << std::endl;
      for (const auto e : c.first) { 
        std::cout << "\t" << e;
      }
      std::cout << std::endl;
      c.second->print_node();
      std::cout << std::endl;
    }
  } else {
    std::cout << "Leaf:" << std::endl;
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
    return node.get();
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
  bool inside = false;
  for (int i = 0, j = 0; i < dimensions; ++i, j+=2) {
    inside = entry[i] >= rect[j] && entry[i] <= rect[j+1];
    if (!inside) {
      return false;
    }
  }
  return inside;
}
  

#endif
