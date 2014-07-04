#ifndef TREE_H
#define TREE_H

#include <list>
#include <tuple>

template <class T> class Tree {
  protected:

    // This is instead of a node class, might be genious, might be stupid.
    template <class T> struct node {
      std::list< std::tuple< double, double, double, T > > children;
    };
    
    //Not sure about this list, it's getting late.
    std::list< node<T> > nodes;
  public:
    Tree() {}
    virtual T search() = 0;
    virtual void insert(T) = 0;
    /*virtual void del(T);
    virtual void condense();
    virtual void adjust();*/
};

#endif
