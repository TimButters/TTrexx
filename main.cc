#include "src/rtree.h"

int main(int argc, char *argv[])
{
  RTree<std::vector<int> > tree;

  std::vector<int> point = {5, 6};
  tree.insert(point);
  
  point[0] = 7;
  point[1] = 7;
  std::cout << "2" << std::endl;
  tree.insert(point);
  
  point[0] = 4;
  point[1] = 4;
  std::cout << "3" << std::endl;
  tree.insert(point);
  
  point[0] = 0;
  point[1] = 0;
  std::cout << "4" << std::endl;
  tree.insert(point);
  
  point[0] = 4;
  point[1] = 3;
  //std::cout << "5" << std::endl;
  //tree.insert(point);
  
  tree.print_tree();

  return 0;
}
