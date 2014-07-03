#ifndef TREE_H
#define TREE_H

#include <list>
#include <tuple>

template <class T> class Tree {
  protected:
    std::list< std::tuple<double, double, double, T> > children;
  public:
    Tree() {}
    virtual T search() = 0;
    virtual void insert(T) = 0;
    /*virtual void del(T);
    virtual void condense();
    virtual void adjust();*/
};

#endif
