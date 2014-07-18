#ifndef NODE_H
#define NODE_H

#include <list>
#include <vector>
#include <limits>
#include <memory>
#include <utility>
#include <iostream>
#include <algorithm>


template <class T> class Node {
  protected:
    typedef std::vector<double> MBR;
    typedef std::unique_ptr< Node<T> > NodePtr;
    typedef std::pair<MBR, NodePtr> NodePair;
    typedef std::list<NodePair> NodeList;

    int level_;
    bool leaf;
    Node<T>* up_ = NULL;
  
  public:
    NodeList children;
    std::list<T> entries;
    
    Node() {leaf = false;}
    Node(std::list<T>, Node<T>*);

    //void set_leaf(bool b) {leaf = b;}
    bool is_leaf()        {return leaf;}
    Node<T>* up()         {return up_;}
    int level()           {return level_;}
    
    NodePair split(Node<T>*, bool recalc_box=false);
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

template <class T> Node<T>::Node(std::list<T> elems, Node<T> *above)
{
  entries = elems;
  leaf = true;
  up_ = above;
}

template <class T> 
typename Node<T>::NodePair Node<T>::split(Node<T> *above, bool recalc_box)
{
  //Simple mock up function to split node.
  //if (leaf) {
    int n = entries.size();
    std::list<T> tmp_list;
    typename std::list<T>::iterator iter = entries.begin();
    advance(iter, n/2);
    std::copy(iter, entries.end(), std::back_inserter(tmp_list));
    entries.erase(iter, entries.end());

    if (recalc_box) {
      auto index = std::find_if(above->children.begin(), above->children.end(), 
                                [this](NodePair const& elem) {
                                  return elem.second.get() == this;
                                 });
      index->first = find_mbr(entries);
    }
    return std::make_pair(find_mbr(tmp_list), NodePtr(new Node<T>(tmp_list, above)));
  //} else {

  //}
}

template <class T>
typename Node<T>::MBR Node<T>::find_mbr(std::list<T> points)
{
  int dim = points.front().size();
  MBR rect(2*dim);
  for (int i = 0, count = 0; i < 2*dim; i+=dim, ++count) {
    double max = -std::numeric_limits<double>::infinity();
    double min = std::numeric_limits<double>::infinity();
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

double operator- (std::vector<double> &lhs, std::vector<double> &rhs)
{
  double lhs_area = 1;
  for (int i = 0; i<rhs.size(); i+=2) {
    lhs_area *= lhs[i+1] - lhs[i];
  }
  double rhs_area = 1;
  for (int i = 0; i<rhs.size(); i+=2) {
    rhs_area *= rhs[i+1] - rhs[i];
  }
  return lhs_area - rhs_area;
}

#endif
