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


  auto find_it = tree.position_of(3);
  std::cout<<*find_it<<std::endl;

  tree.print();
//  tree.clear();

/*
  auto newit = tree.find(3);
  std::cout<<*newit<<std::endl;

  newit = tree.find(1212);
  */
 


  return 0;
}
