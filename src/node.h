#ifndef NODE_H
#define NODE_H

#include <list>
#include <vector>
#include <utility>
#include <memory>
#include <iostream>
#include <algorithm>


template <class T> class Node {
  protected:
    typedef std::vector<double> MBR;
    typedef std::unique_ptr< Node<T> > NodePtr;
    typedef std::pair<MBR, NodePtr> NodePair;
    typedef std::list<NodePair> NodeList;

    //std::list<T> entries;
    int level_;
    bool leaf;
    //T entry;
  
  public:
    NodeList children;
    std::list<T> entries;
    
    Node() {leaf = false;}
    Node(std::list<T>);
    //T get_entry() {return entry;}
    bool is_leaf() {return leaf;}
    void set_leaf(bool b) {leaf = b;}
    int level() {return level_;}
    NodePair split();
    static MBR find_mbr(std::list<T>);

    void print_node();
};

template <class T>
std::ostream& operator<<(std::ostream &out, const std::pair<T, T> rhs)
{
  out << rhs.first << "\t" << rhs.second;
  return out;
}

template <class T>
std::ostream& operator<<(std::ostream &out, const std::vector<T> rhs)
{
  for (auto &val : rhs) {
    out << val << "\t";
  }
  out << std::endl;
  return out;
}

template <class T> Node<T>::Node(std::list<T> elems)
{
  entries = elems;
  leaf = true;
}

template <class T> 
typename Node<T>::NodePair Node<T>::split()
{
  //Simple mock up function to split node.
  //if (leaf) {
    int n = entries.size();
    std::list<T> tmp_list;
    typename std::list<T>::iterator iter = entries.begin();
    advance(iter, n/2);
    std::copy(iter, entries.end(), std::back_inserter(tmp_list));
    entries.erase(iter, entries.end());
    return std::make_pair(find_mbr(tmp_list), NodePtr(new Node<T>(tmp_list)));
  //} else {

  //}
}

template <class T>
typename Node<T>::MBR Node<T>::find_mbr(std::list<T> points)
{
  int dim = points.front().size();
  MBR rect(2*dim);
  for (int i = 0, count = 0; i < 2*dim; i+=dim, ++count) {
    /* making these doubles violates template! */
    double max = -10000; //make -inf
    double min = 10000;// make inf
    for (const auto &p : points) {
      typename T::const_iterator iter = p.begin();
      advance(iter, count);
      for (int j = 0; j < p.size(); iter += dim, j += dim) {
        if (*iter > max) max = *iter;
        if (*iter < min) min = *iter;
      }
    }
    rect[i] = min;
    rect[i+1] = max;
  }
  return rect;
}

template <class T> void Node<T>::print_node()
{
  if (!leaf) {
    for (const auto &c : children) {
      std::cout << "Rect:" << std::endl;
      for (const auto e : c.first) { 
        std::cout << "\t" << e;
        c.second->print_node();
      }
      std::cout << std::endl;
    }
  } else {
    std::cout << "Leaf:" << std::endl;
    for (auto e : entries) {
      std::cout << e << std::endl;
    }
  }
}


#endif
