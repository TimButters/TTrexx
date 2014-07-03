#include "src/rtree.h"

int main(int argc, char *argv[])
{
  RTree<char> tree;

  tree.insert('s');
  tree.print_tree();

  return 0;
}
