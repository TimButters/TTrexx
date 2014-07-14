#ifndef NODE_H
#define NODE_H

#include <list>
#include <vector>
#include <utility>
#include <memory>
#include <iostream>


template <class T> class Node {
  protected:
    typedef std::vector<double> MBR;
    typedef std::unique_ptr< Node<T> > NodePtr;
    typedef std::list< std::pair<MBR, NodePtr> > NodeList;

    //std::list<T> entries;
    int level_;
    bool leaf;
    T entry;
  
  public:
    NodeList children;
    std::list<T> entries;
    
    Node() {leaf = false;}
    Node(T);
    T get_entry() {return entry;}
    bool is_leaf() {return leaf;}
    void set_leaf(bool b) {leaf = b;}
    int level() {return level_;}
    virtual void polymorph() {}
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

template <class T> Node<T>::Node(T elem)
{
  entry = elem;
  leaf = true;
}

#endif
