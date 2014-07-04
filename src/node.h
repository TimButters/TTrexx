#ifndef NODE_H
#define NODE_H

#include <list>
#include <vector>
#include <utility>
#include <memory>


template <class T> class Node {
  protected:
    typedef std::vector<double> MBR;
    typedef std::unique_ptr< Node<T> > NodePtr;
    typedef std::list< std::pair<MBR, NodePtr> > NodeList;

    NodeList children;
    int level;
    bool leaf;
    T entry;
  
  public:
    Node() {leaf = false;}
    Node(T);
    T get_entry() {return entry;}
    bool is_leaf() {return leaf;}

};

template <class T> Node<T>::Node(T elem)
{
  entry = elem;
  leaf = true;
}

#endif
