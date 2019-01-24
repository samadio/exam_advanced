/**
 * @file main.cc
 * @brief main file for the exam
 * 
 * @author William WIlson
 * 
 * @date 1/2/23
 */

#include <memory>
#include"BST.h"
// Here all the testing will be done

int main() {
  
  int a = 1;
  NodeNamespace::BSTNode<int,int> test;

  auto tree = BSTree<int,int>();
  tree.insert(8,8);
  tree.insert(3,3);
  tree.insert(a,a);
  tree.insert(10,10);
  tree.insert(6,6);
  tree.insert(4,4);
  tree.insert(7,7);
  tree.insert(14,14);
  tree.insert(13,13);
  tree.insert(1,1);

  std::cout<<"Searching for key 3 and editing the content to 3000"<<std::endl;
  auto find_it = tree.position_of(3);
  find_it .get() -> content.second = 3000;
 // find_it.get() -> content.first = 3000; //compiler error

  std::cout<<"tree print"<<std::endl;
  tree.print();
  
  std::cout<<"cout tree"<<std::endl;
  std::cout<<tree<<std::endl;
  tree.insert(5,5);
  tree.insert(6,6);
  tree.print();
  tree.clear();
 

  auto testtree = BSTree<int,int>();
  testtree.insert_pair(std::make_pair(8,8));
  testtree.insert_pair(std::make_pair(3,3));
  testtree.insert_pair(std::make_pair(1,1));
  testtree.insert_pair(std::make_pair(10,10));
  testtree.insert_pair(std::make_pair(6,6));
  testtree.insert_pair(std::make_pair(4,4));
  testtree.insert_pair(std::make_pair(7,7));
  testtree.insert_pair(std::make_pair(14,14));
  testtree.insert_pair(std::make_pair(13,13));
  testtree.insert_pair(std::make_pair(1,1));

  std::cout<<"Searching for key 3 and editing the content to 3000"<<std::endl;
  auto test_it = testtree.position_of(3);
  test_it.get() -> content.second = 3000; //works fine
 // test_it.get() -> content.first = 3000; //compiler error
  

  testtree.print();


  return 0;
}
