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
  
  int a =1, b=2;
  NodeNamespace::BSTNode<int,int> test;
//  auto test2 = BSTNode<int,int>(a,b);

  auto tree = BSTree<int,int>();
  tree.insert(8,8);
  tree.insert(3,3);
  tree.insert(1,1);
  tree.insert(10,10);
  tree.insert(6,6);
  tree.insert(4,4);
  tree.insert(7,7);
  tree.insert(14,14);
  tree.insert(13,13);
  tree.insert(1,1);

  std::cout<<"Searching for key 3"<<std::endl;
  auto find_it = tree.position_of(3);
  std::cout<<(*find_it).second<<std::endl;

  std::cout<<"tree print"<<std::endl;
  tree.print();
  
  std::cout<<"cout tree"<<std::endl;
  std::cout<<tree<<std::endl;
  tree.insert(5,5);
  tree.insert(6,6);
  tree.print();
  std::cout<<"Content of key 6 is "<<tree[6]<<std::endl;
  tree.clear();

/*
  auto newit = tree.find(3);
  std::cout<<*newit<<std::endl;

  newit = tree.find(1212);
  */
 


  return 0;
}
