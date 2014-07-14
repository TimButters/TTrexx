#include "src/rtree.h"

int main(int argc, char *argv[])
{
  RTree<std::vector<int> > tree;

  std::vector<int> point = {2, 3};
  tree.insert(point);
  point[0] = 5;
  point[1] = 5;
  tree.insert(point);
  point[0] = 6;
  point[1] = 2;
  tree.insert(point);
  point[0] = 9;
  point[1] = 9;
  tree.insert(point);
  point[0] = 0;
  point[1] = 0;
  tree.insert(point);
  
  tree.print_tree();

  return 0;
}
