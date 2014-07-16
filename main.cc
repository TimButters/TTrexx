#include "src/rtree.h"

int main(int argc, char *argv[])
{
  RTree<std::vector<int> > tree;

  std::cout << "Put some values into new R-Tree..." << std::endl;
  std::vector<int> point = {5, 6};
  tree.insert(point);
  
  point[0] = 7;
  point[1] = 7;
  tree.insert(point);
  
  point[0] = 4;
  point[1] = 4;
  tree.insert(point);
  
  tree.print_tree();
  /****************/
  
  std::cout << std::endl << "---------------------------------------------" << std::endl; 
  std::cout << "The next addition overflows the root node.\n"
            << "Split the node and increase the tree height.\n" << std::endl;
  
  point[0] = 0;
  point[1] = 0;
  tree.insert(point);

  tree.print_tree();
  /****************/

  std::cout << std::endl << "---------------------------------------------" << std::endl; 
  std::cout << "Add a new point that lies within one of the leaf node rectangles...\n" << std::endl;
  
  point[0] = 2;
  point[1] = 2;
  tree.insert(point);
  
  tree.print_tree();
  /****************/
  
  std::cout << std::endl << "---------------------------------------------" << std::endl; 
  std::cout << "Add a new point that is outside the current leaf node rectangles.\n" 
            << "Find the leaf node that requires the least expansion to its bounding\n" 
            << "rectangle and insert the new point.\n" << std::endl;
  
  point[0] = 6;
  point[1] = 8;
  tree.insert(point);
  
  tree.print_tree();

  return 0;
}
